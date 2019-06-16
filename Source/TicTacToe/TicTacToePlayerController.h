// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TicTacToeActor.h"
#include "TicTacToePlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ATicTacToePlayerController : public APlayerController, public ITicTacToeActor
{
	GENERATED_BODY()

public:
	ATicTacToePlayerController();

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


