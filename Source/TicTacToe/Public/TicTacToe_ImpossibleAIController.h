// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TicTacToeBlock.h"
#include "TicTacToeDefinitionsHolder.h"
#include "TicTacToeActor.h"
#include "TicTacToe_ImpossibleAIController.generated.h"

/**
 * 
 */
UCLASS()
class ATicTacToe_ImpossibleAIController : public AAIController, public ITicTacToeActor
{
	GENERATED_BODY()
	
public:
	ATicTacToe_ImpossibleAIController();

	// add IActor
	UPROPERTY()
	int32 Priority;

	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Block Type")
	EBlockType MyBlockType;

	class ITicTacToeActor* Enemy;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="AI STUFF")
		FIntPoint GetTargetBlockPosition(const TArray<ATicTacToeBlock*>& blockArray);
		virtual FIntPoint GetTargetBlockPosition_Implementation(const TArray<ATicTacToeBlock*>& blockArray) override;

protected:
	FIntPoint NotPlacedPosition;

	FIntPoint MiddleChoice;

	TArray<FIntPoint> EdgeChoices;

	TArray<FIntPoint> CornerChoices;

private:
	FIntPoint MirrorPos(FIntPoint point);
	FIntPoint GetPlacedBlockPos(TArray<FIntPoint> Choices, TArray<ATicTacToeBlock*> blockArray);
};
