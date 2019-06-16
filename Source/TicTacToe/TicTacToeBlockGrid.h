// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/TicTacToeDefinitionsHolder.h"
#include "TicTacToeBlock.h"
#include "TicTacToeBlockGrid.generated.h"

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class ATicTacToeBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* EndText;

public:
	ATicTacToeBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;

	/** Current turn role */
	EBlockType CurrentType;
	/** Current win state */
	EWinState WinState;
	/** Current match state */
	bool IsInMatch;
	/** Current pause state */
	bool IsInPause;

	/** Current game state by int. 0 to in match, 1 to circle win, -1 to cross win, 2 to draw game, 3 to in pause. */
	//int CurrentGameState;

	/** Array of owning blocks */
	TArray<ATicTacToeBlock*> BlockArray;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	void AddScore();

	EBlockType GetCurrentType();

	void ChangeTurn();

	/** Handle the turn when block is being clicked */
	void HandleTurn(ATicTacToeBlock* executedBlock);

	/** Handle calling AI on pre-next turn */
	void OnPreNextTurn();

	/** Returns winner block type. 0 to none, 1 to circle win, -1 to cross win, 2 to draw. */
	EWinState CheckWin(ATicTacToeBlock* checkBlock); // TODO: fix magic number

	/** Returns position of array from 2D vector */
	int GetIndex(int num_x, int num_y);
	/** Returns position of array from item of array */
	int GetIndex(ATicTacToeBlock * block_pos);

	/** Handle the resetting game */
	void ResetGame();

	/** Handle the game end */
	void HandleGameEnd(); // TODO: implement this.

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



