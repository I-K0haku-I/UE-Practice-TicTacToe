// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TicTacToePlayerController.h"

ATicTacToePlayerController::ATicTacToePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
