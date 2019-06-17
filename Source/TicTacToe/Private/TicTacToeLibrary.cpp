// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToeLibrary.h"
#include "TicTacToeBlock.h"
#include "TicTacToeDefinitionsHolder.h"


UTicTacToeLibrary::UTicTacToeLibrary(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}


int UTicTacToeLibrary::GetIndex(int numX, int numY)
{
	return  numX + (numY * 3);
}

int UTicTacToeLibrary::GetIndex(FIntPoint point)
{
	return GetIndex(point.X, point.Y);
}

FIntPoint UTicTacToeLibrary::GetPos(int32 index)
{
	return FIntPoint(index - (int)(index / 3) * 3, index / 3);
}

bool UTicTacToeLibrary::CanWinWithBlock(FIntPoint blockPosition, EBlockType winningBlockType, TArray<ATicTacToeBlock*> blockArray)
{
    int32 winIndex = UTicTacToeLibrary::GetIndex(blockPosition.X, blockPosition.Y);
    EBlockType originalBlockType = blockArray[winIndex]->GetBlockType(); blockArray[winIndex]->SetBlockType(winningBlockType);
    int32 dimension = blockArray.Num();

    int32 diagonal = 0;
    int32 diagonalReverse = 0;
    int32 horizontal = 0;
    int32 vertical = 0;

    for (int32 i = 0; i < dimension; i++)
    {
        if (blockArray[UTicTacToeLibrary::GetIndex(blockPosition.X, i)]->GetBlockType() == winningBlockType)
            horizontal++;
        if (blockArray[UTicTacToeLibrary::GetIndex(i, blockPosition.Y)]->GetBlockType() == winningBlockType)
            vertical++;
        if (blockArray[UTicTacToeLibrary::GetIndex(i, i)]->GetBlockType() == winningBlockType)
            diagonal++;
        if (blockArray[UTicTacToeLibrary::GetIndex(i, dimension - i - 1)]->GetBlockType() == winningBlockType)
            diagonalReverse++;
    }
    blockArray[winIndex]->SetBlockType(originalBlockType);
    TArray<int32> results = {diagonal, diagonalReverse, horizontal, vertical};
    bool canWin = results.Contains(dimension);
    return canWin;
}