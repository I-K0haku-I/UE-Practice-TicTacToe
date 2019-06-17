// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToe_ImpossibleAIController.h"
#include "TicTacToeBlock.h"
#include "TicTacToeDefinitionsHolder.h"
#include "TicTacToeLibrary.h"


ATicTacToe_ImpossibleAIController::ATicTacToe_ImpossibleAIController()
{

    Priority = 9999;
}

FIntPoint ATicTacToe_ImpossibleAIController::GetTargetBlockPosition_Implementation(const TArray<ATicTacToeBlock*>& blockArray)
{
    // make winning move or prevent enemy from winning if you can
    FIntPoint winninPosition = NotPlacedPosition;
    FIntPoint preventivePosition = NotPlacedPosition;
    ATicTacToeBlock* block;
    for (int32 i = 0; i < blockArray.Num(); i++)
    {
        block = blockArray[i];
        if (block->GetBlockType() == EBlockType::None)
        {
            FIntPoint position = UTicTacToeLibrary::GetPos(i);
            if (UTicTacToeLibrary::CanWinWithBlock(position, block->GetBlockType(), blockArray))
                return position;
            if (UTicTacToeLibrary::CanWinWithTile(position, Enemy->MyBlockType, blockArray))
                preventivePosition = position;
        }
    }
    if (preventivePosition != NotPlacedPosition)
        return preventivePosition;
    
    // place middle
    if (blockArray[UTicTacToeLibrary::GetIndex(MiddleChoice)]->GetBlockType() == EBlockType::None)
        return MiddleChoice;
    
    // check if edge tile placed
    FIntPoint edgeTileOccupied = GetPlacedBlockPos(CornerChoices, blockArray);
    
    // place edge if not placed
    if (edgeTileOccupied == NotPlacedPosition)
    {
        FIntPoint result;
        FIntPoint mirroredResult;
        do
        {
            int i = FMath::RandRange(0, EdgeChoices.Num());
            result = EdgeChoices[i];
            mirroredResult = MirrorPos(result);
        } while (blockArray[UTicTacToeLibrary::GetIndex(result)]->GetBlockType() != EBlockType::None || blockArray[UTicTacToeLibrary::GetIndex(mirroredResult)]->GetBlockType() != EBlockType::None);
        return result;
    }

    // check if corner tile placed
    FIntPoint cornerTileOccupied = GetPlacedBlockPos(CornerChoices, blockArray);
    
    // place corner if not placed
    if (cornerTileOccupied == NotPlacedPosition)
    {
        FIntPoint result;
        
    }
    
    return FIntPoint(1, 1);
}

FIntPoint ATicTacToe_ImpossibleAIController::MirrorPos(FIntPoint point)
{
    point.X = point.X == 0 ? 2 : (point.X == 2 ? 0 : 1);
    point.Y = point.Y == 0 ? 2 : (point.Y == 2 ? 0 : 1);
    return point;
}

FIntPoint ATicTacToe_ImpossibleAIController::GetPlacedBlockPos(TArray<FIntPoint> Choices, TArray<ATicTacToeBlock*> blockArray)
{
    FIntPoint blockOccupied;
    for (int32 i = 0; i < blockArray.Num(); i++)
        if (Choices.Contains(UTicTacToeLibrary::GetPos(i)) && MyBlockType == blockArray[i]->GetBlockType())
            return UTicTacToeLibrary::GetPos(i);
    return NotPlacedPosition;
}