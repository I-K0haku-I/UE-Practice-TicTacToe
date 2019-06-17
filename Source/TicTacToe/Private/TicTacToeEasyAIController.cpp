// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacToeEasyAIController.h"
#include "TicTacToeBlock.h"
#include "TicTacToeLibrary.h"

ATicTacToeEasyAIController::ATicTacToeEasyAIController()
{
    Priority = 4;

}


FIntPoint ATicTacToeEasyAIController::GetTargetBlockPosition_Implementation(const TArray<ATicTacToeBlock*>& blockArray)
{
    TArray<ATicTacToeBlock*> emptyBlocksArray;
    for (int32 i = 0; i < blockArray.Num(); i++)
        if (blockArray[i]->GetBlockType() == EBlockType::None)
            emptyBlocksArray.Add(blockArray[i]);

    if (emptyBlocksArray.Num() == 0)
        throw "Do not call AI if no moves possible.";

    ATicTacToeBlock* block = emptyBlocksArray[FMath::RandRange(0, emptyBlocksArray.Num() - 1)];
    return FIntPoint(UTicTacToeLibrary::GetPos(blockArray.Find(block)));
}

