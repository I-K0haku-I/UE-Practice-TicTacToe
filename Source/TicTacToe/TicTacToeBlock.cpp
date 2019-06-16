// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicTacToeBlock.h"
#include "TicTacToeBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include "Public/TicTacToeDefinitionsHolder.h"

#define TOSTR(var) #var

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
	if (BlockType != EBlockType::None || !OwningGrid->IsInMatch)
	{
		return;
	}

	// Tell the Grid
	OwningGrid->HandleTurn(this);
}

UMaterialInterface* ATicTacToeBlock::GetMaterialByType(EBlockType _type) {
	switch (_type)
	{
	case EBlockType::Circle:
		return OrangeMaterial;
	case EBlockType::Cross:
		return BlueMaterial;
	case EBlockType::None:
		return BaseMaterial;
	default:
		return BaseMaterial;
	}
}

void ATicTacToeBlock::Highlight(bool bOn)
{
	UE_LOG(LogTemp, VeryVerbose, TEXT("TILEARRAYPOS: %d, BLOCKTYPE: %s, INMATCH: %s, WINSTATE: %s"), OwningGrid->GetIndex(this), TOSTR(BlockType), TOSTR(OwningGrid->IsInMatch), TOSTR(OwningGrid->WinState));
	// Do not highlight if the block has already been activated or if the current game state has not set to 0.
	if (BlockType != EBlockType::None || !OwningGrid->IsInMatch)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, HighlightMaterial);
	}
	else
	{
		SetMaterialByType(BlockType);
	}
}

void ATicTacToeBlock::SetType(EBlockType _type)
{
	SetMaterialByType(_type);
	BlockType = _type;
}

EBlockType ATicTacToeBlock::GetBlockType()
{
	return BlockType;
}

void ATicTacToeBlock::SetMaterialByType(EBlockType _type)
{
	UE_LOG(LogTemp, Verbose, TEXT("Changing material to %s!"), TOSTR(_type));
	UMaterialInterface* matI;
	matI = GetMaterialByType(_type);
	BlockMesh->SetMaterial(0, matI);

}
