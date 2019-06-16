// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TicTacToeBlock.h"
#include "TicTacToeDefinitionsHolder.h"
#include "TicTacToe_ImpossibleAIController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToe_ImpossibleAIController : public AAIController
{
	GENERATED_BODY()
	
	// add IActor
	UPROPERTY()
	int32 Priority;

	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Block Type")
	EBlockType MyBlockType;

public:
	FIntPoint GetTargetBlockPosition(TArray<ATicTacToeBlock*> blockArray);

protected:
	FIntPoint NotPlacedPosition;

	FIntPoint MiddleChoice;

	TArray<FIntPoint> EdgeChoices;

	TArray<FIntPoint> CornerChoices;

private:
	bool CanWinWithTile(FIntPoint tilePos, EBlockType blockType, TArray<ATicTacToeBlock*> blockArray);

	int GetIndex(int numX, int numY);
};
