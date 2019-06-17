// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TicTacToeLibrary.generated.h"
#include "TicTacToeDefinitionsHolder.h"
#include "TicTacToeBlock.h"

UCLASS()
class UTicTacToeLibrary : public UObject
{
	GENERATED_UCLASS_BODY()

	static int GetIndex(int numX, int numY);
	static int GetIndex(FIntPoint point);
	static FIntPoint GetPos(int32 index);
	static bool CanWinWithBlock(FIntPoint blockPosition, EBlockType winningBlockType, TArray<ATicTacToeBlock*> blockArray);
};
