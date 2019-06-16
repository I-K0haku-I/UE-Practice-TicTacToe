// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/TicTacToeDefinitionsHolder.h"
#include "TicTacToeBlock.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBlock, Log, Verbose);
/** A block that can be clicked */
UCLASS(minimalapi)
class ATicTacToeBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	/** Which type are we currently? */
	EBlockType BlockType; // magic numbers not so good, should be enum

public:
	ATicTacToeBlock();

	/** Pointer to white material used on default block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Pointer to darker material used on the focused block */
	UPROPERTY()
	class UMaterialInstance* HighlightMaterial;

	/** Pointer to blue material used on cross blocks */
	UPROPERTY()
	class UMaterialInstance* BlueMaterial;

	/** Pointer to orange material used on circle blocks */
	UPROPERTY()
	class UMaterialInstance* OrangeMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class ATicTacToeBlockGrid* OwningGrid;

	/** Handle the block being clicked */
	UFUNCTION()
	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the block being touched  */
	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	/** Gets the material by type */
	UMaterialInterface* GetMaterialByType(EBlockType _type); // magica numba

	void Highlight(bool bOn);

	/** Sets the type of block */
	void SetType(EBlockType _type);

	EBlockType GetBlockType();

	bool IsClickable();

private:
	/** Sets the material by type */
	void SetMaterialByType(EBlockType _type);

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
};



