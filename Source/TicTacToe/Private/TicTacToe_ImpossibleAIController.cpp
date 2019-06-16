// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToe_ImpossibleAIController.h"
#include "TicTacToeBlock.h"
#include "TicTacToeDefinitionsHolder.h"

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
            FIntPoint position = GetPos(i);
            if (CanWinWithTile(position, block->GetBlockType(), blockArray))
                return position;
            if (CanWinWithTile(position, Enemy->MyBlockType, blockArray))
                preventivePosition = position;
        }
    }
    if (preventivePosition != NotPlacedPosition)
        return preventivePosition;
    
    // place middle
    if (blockArray[GetIndex(MiddleChoice)]->GetBlockType() == EBlockType::None)
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
        } while (blockArray[GetIndex(result)]->GetBlockType() != EBlockType::None || blockArray[GetIndex(mirroredResult)]->GetBlockType() != EBlockType::None);
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

int ATicTacToe_ImpossibleAIController::GetIndex(FIntPoint point)
{
	return GetIndex(point.X, point.Y);
}

FIntPoint ATicTacToe_ImpossibleAIController::GetPos(int32 index)
{
	return FIntPoint(index - (int)(index / 3) * 3, index / 3);
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
        if (Choices.Contains(GetPos(i)) && MyBlockType == blockArray[i]->GetBlockType())
            return GetPos(i);
    return NotPlacedPosition;
}