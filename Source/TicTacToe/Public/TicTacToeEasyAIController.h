// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TicTacToeDefinitionsHolder.h"
#include "TicTacToeActor.h"
#include "TicTacToeEasyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TICTACTOE_API ATicTacToeEasyAIController : public AAIController, public ITicTacToeActor
{
	GENERATED_BODY()
	
public:
	ATicTacToeEasyAIController();

	// add IActor
	UPROPERTY()
	int32 Priority;

	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Block Type")
	EBlockType MyBlockType;

	class ITicTacToeActor* Enemy;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="AI STUFF")
		FIntPoint GetTargetBlockPosition(const TArray<ATicTacToeBlock*>& blockArray);
		virtual FIntPoint GetTargetBlockPosition_Implementation(const TArray<ATicTacToeBlock*>& blockArray) override;

};
