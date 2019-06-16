// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToe_ImpossibleAIController.h"
#include "TicTacToeBlock.h"
#include "TicTacToeDefinitionsHolder.h"

ATicTacToe_ImpossibleAIController::ATicTacToe_ImpossibleAIController()
{

    Priority = 9999;
}

FIntPoint ATicTacToe_ImpossibleAIController::GetTargetBlockPosition(TArray<ATicTacToeBlock*> blockArray)
{
    return FIntPoint(3, 2);
}


bool ATicTacToe_ImpossibleAIController::CanWinWithTile(FIntPoint tilePos, EBlockType winningBlockType, TArray<ATicTacToeBlock*> blockArray)
{
    int32 winIndex = GetIndex(tilePos.X, tilePos.Y);
    EBlockType originalBlockType = blockArray[winIndex]->GetBlockType(); blockArray[winIndex]->SetBlockType(winningBlockType);
    int32 dimension = blockArray.Num();

    int32 diagonal = 0;
    int32 diagonalReverse = 0;
    int32 horizontal = 0;
    int32 vertical = 0;

    for (int32 i = 0; i < dimension; i++)
    {
        if (blockArray[GetIndex(tilePos.X, i)]->GetBlockType() == winningBlockType)
            horizontal++;
        if (blockArray[GetIndex(i, tilePos.Y)]->GetBlockType() == winningBlockType)
            vertical++;
        if (blockArray[GetIndex(i, i)]->GetBlockType() == winningBlockType)
            diagonal++;
        if (blockArray[GetIndex(i, dimension - i - 1)]->GetBlockType() == winningBlockType)
            diagonalReverse++;
    }
    blockArray[winIndex]->SetBlockType(originalBlockType);
    TArray<int32> results = {diagonal, diagonalReverse, horizontal, vertical};
    bool canWin = results.Contains(dimension);
    return canWin;
}


int ATicTacToe_ImpossibleAIController::GetIndex(int numX, int numY)
{
	return  numX + (numY * 3);
}