// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TicTacToeDefinitionsHolder.h"
#include "TicTacToeBlock.h"
#include "TicTacToeActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTicTacToeActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TICTACTOE_API ITicTacToeActor
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	int32 Priority;

	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Block Type")
	EBlockType MyBlockType;

	class ITicTacToeActor* Enemy;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="AI STUFF")
	FIntPoint GetTargetBlockPosition(const TArray<ATicTacToeBlock*>& blockArray);
};
