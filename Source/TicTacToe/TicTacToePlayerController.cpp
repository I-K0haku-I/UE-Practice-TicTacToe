// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicTacToePlayerController.h"

ATicTacToePlayerController::ATicTacToePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
    
	Priority = 5;
}


FIntPoint ATicTacToePlayerController::GetTargetBlockPosition_Implementation(const TArray<ATicTacToeBlock*>& blockArray)
{
	return FIntPoint(0, 0);
}
