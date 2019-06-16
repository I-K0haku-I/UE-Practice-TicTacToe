// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"


UENUM()
enum class EBlockType : uint8
{
	None,
	Cross,
	Circle,
};

UENUM()
enum class EWinState : uint8
{
	None,
	Cross,
	Circle,
	Draw,
};

/**
 * 
 */
// class TICTACTOE_API TicTacToeDefinitionsHolder
// {
// public:
// 	TicTacToeDefinitionsHolder();
// 	~TicTacToeDefinitionsHolder();

// };
