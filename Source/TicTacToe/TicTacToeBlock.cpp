// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlock.h"
#include "TicTacToeBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ATicTacToeBlock::ATicTacToeBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> HighlightMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, HighlightMaterial(TEXT("/Game/Puzzle/Meshes/HighlightMaterial.HighlightMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f, 1.f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ATicTacToeBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ATicTacToeBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	HighlightMaterial = ConstructorStatics.HighlightMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
}

void ATicTacToeBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ATicTacToeBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ATicTacToeBlock::HandleClicked()
{
	// Do not handle click if the block has already been activated or current game state are not in match.
	if (BlockType != 0 || OwningGrid->CurrentGameState != 0)
	{
		return;
	}

	// Tell the Grid
	OwningGrid->HandleTurn(this);
}

UMaterialInterface* ATicTacToeBlock::GetMaterialByType(int Type) {
	switch (Type)
	{
	case 1:
		return OrangeMaterial;
	case -1:
		return BlueMaterial;
	default:
		return BaseMaterial;
	}
}

void ATicTacToeBlock::Highlight(bool bOn)
{
	UE_LOG(LogTemp, VeryVerbose, TEXT("TILEARRAYPOS: %d, BLOCKTYPE: %d, CURRENTGAMESTATE: %d"), OwningGrid->GetPosition(this), BlockType, OwningGrid->CurrentGameState);
	// Do not highlight if the block has already been activated or if the current game state has not set to 0.
	if (BlockType != 0 || OwningGrid->CurrentGameState != 0)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, HighlightMaterial);
	}
	else
	{	// Using GetMaterialByType for fail safe
		BlockMesh->SetMaterial(0, GetMaterialByType(BlockType));
	}
}

void ATicTacToeBlock::SetMaterialByType(int _type)
{
	UMaterialInterface* matI = GetMaterialByType(_type);
	BlockMesh->SetMaterial(0, matI);
}

void ATicTacToeBlock::SetType(int _type)
{
	SetMaterialByType(_type);
	BlockType = _type;
}
