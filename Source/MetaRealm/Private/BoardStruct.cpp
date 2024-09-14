// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardStruct.h"

void FBoardStruct::PrintStruct()
{
	UE_LOG(LogTemp, Warning, TEXT("Current Board Data : %s"), *ContentString);
}
