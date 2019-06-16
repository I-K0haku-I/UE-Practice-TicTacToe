// Fill out your copyright notice in the Description page of Project Settings.


#include "TicTacToeLibrary.h"

UTicTacToeLibrary::UTicTacToeLibrary(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}


int UTicTacToeLibrary::GetIndex(int numX, int numY)
{
	return  numX + (numY * 3);
}

int UTicTacToeLibrary::GetIndex(FIntPoint point)
{
	return GetIndex(point.X, point.Y);
}

FIntPoint UTicTacToeLibrary::GetPos(int32 index)
{
	return FIntPoint(index - (int)(index / 3) * 3, index / 3);
}
