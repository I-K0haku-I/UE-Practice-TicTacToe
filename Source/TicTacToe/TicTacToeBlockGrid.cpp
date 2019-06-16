// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlockGrid.h"
#include "TicTacToeBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "Public/TicTacToeDefinitionsHolder.h"

#define TOSTR(var) #var
#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATicTacToeBlockGrid::ATicTacToeBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
	CurrentType = EBlockType::Cross;
}


void ATicTacToeBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("Initializing!"));

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ATicTacToeBlock* NewBlock = GetWorld()->SpawnActor<ATicTacToeBlock>(BlockLocation, FRotator(0, 0, 0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
			BlockArray.Add(NewBlock);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Initalizing completed!"));

	// Allow player inputs
	IsInMatch = true;

}


void ATicTacToeBlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

EBlockType ATicTacToeBlockGrid::GetCurrentType()
{
	return CurrentType;
}

void ATicTacToeBlockGrid::ChangeTurn()
{
	CurrentType = CurrentType == EBlockType::Circle ? EBlockType::Cross : EBlockType::Circle;
}

void ATicTacToeBlockGrid::HandleTurn(ATicTacToeBlock* executedBlock)
{
	UE_LOG(LogTemp, Verbose, TEXT("Processing turn!"));

	if (!IsInMatch || executedBlock->GetBlockType() != EBlockType::None) {
		return;
	}

	// Set type / material
	executedBlock->SetType(CurrentType);

	WinState = CheckWin(executedBlock);

	UE_LOG(LogTemp, Verbose, TEXT("WINSTATE: %s"), TOSTR(WinState));

	if (WinState == EWinState::None)
	{
		AddScore();
		ChangeTurn();
		OnPreNextTurn();
	}
	else
	{
		HandleGameEnd();
	}
}

void ATicTacToeBlockGrid::OnPreNextTurn()
{
	UE_LOG(LogTemp, VeryVerbose, TEXT("On pre-next turn!"))
		// TODO: implement ai stuff here? maybe?
}

EWinState ATicTacToeBlockGrid::CheckWin(ATicTacToeBlock* checkBlock)
{
	UE_LOG(LogTemp, Verbose, TEXT("Checking win tile!"));

	int arrayPos = GetIndex(checkBlock);

	int by = (int)arrayPos / Size;
	int bx = arrayPos - by * Size;

	int hori = 0;
	int vert = 0;
	int diag = 0;
	int diagRev = 0;

	for (int i = 0; i < Size; i++)
	{
		UE_LOG(LogTemp, VeryVerbose, TEXT("CHECKINGTILEPOS: %d, %d, %d"), bx, i, GetIndex(bx, i));
		if (BlockArray[GetIndex(bx, i)]->GetBlockType() == CurrentType)
			hori++;
		UE_LOG(LogTemp, VeryVerbose, TEXT("CHECKINGTILEPOS: %d, %d, %d"), i, by, GetIndex(i, by));
		if (BlockArray[GetIndex(i, by)]->GetBlockType() == CurrentType)
			vert++;
		UE_LOG(LogTemp, VeryVerbose, TEXT("CHECKINGTILEPOS: %d, %d, %d"), i, (Size - 1 - i), GetIndex(i, (Size - 1 - i)));
		if (BlockArray[GetIndex(i, Size - 1 - i)]->GetBlockType() == CurrentType)
			diag++;
		UE_LOG(LogTemp, VeryVerbose, TEXT("CHECKINGTILEPOS: %d, %d, %d"), i, i, GetIndex(i, i));
		if (BlockArray[GetIndex(i, i)]->GetBlockType() == CurrentType)
			diagRev++;
	}

	UE_LOG(LogTemp, VeryVerbose, TEXT("TILEPOS: %d, %d"), bx, by);
	UE_LOG(LogTemp, VeryVerbose, TEXT("H: %d, V: %d, D: %d, DR: %d"), hori, vert, diag, diagRev);

	if ((hori == Size || vert == Size || diag == Size || diagRev == Size))
		return CurrentType == EBlockType::Circle ? EWinState::Circle : EWinState::Cross;
	else
		for (int n = 0; n != BlockArray.Num(); n++)
		{
			if (BlockArray[n]->GetBlockType() == EBlockType::None)
				return EWinState::None;
		}

	return EWinState::Draw;
}

void ATicTacToeBlockGrid::HandleGameEnd()
{
	UE_LOG(LogTemp, Log, TEXT("Ending!"));

	IsInMatch = false;

	//TODO: Implement game end
	// how do i implement showing reset button? :thinking:

	ResetGame();

}


int ATicTacToeBlockGrid::GetIndex(int num_x, int num_y)
{
	return  num_x + (num_y * Size);
}

int ATicTacToeBlockGrid::GetIndex(ATicTacToeBlock* block_pos)
{
	return BlockArray.Find(block_pos);
}

void ATicTacToeBlockGrid::ResetGame()
{
	UE_LOG(LogTemp, Log, TEXT("Resetting!"));

	// Freeze game before resetting
	//CurrentGameState = 4;
	IsInMatch = false;

	UE_LOG(LogTemp, Verbose, TEXT("Resetting block type!"));

	for (int n = 0; n != BlockArray.Num(); n++)
	{
		BlockArray[n]->SetType(EBlockType::None);
	}

	UE_LOG(LogTemp, Verbose, TEXT("Resetting GameStates!"));

	Score = 0;								// Reset score
	CurrentType = EBlockType::Cross;		// Starting from cross
	//CurrentGameState = 0;					// Enable player inputs
	IsInMatch = true;

	UE_LOG(LogTemp, Log, TEXT("Reset complete!"));
}

#undef LOCTEXT_NAMESPACE
