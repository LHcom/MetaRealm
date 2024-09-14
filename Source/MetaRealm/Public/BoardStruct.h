// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BoardStruct.generated.h"

/**
 * 
 */
USTRUCT(Atomic,BlueprintType)
struct FBoardStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 게시자
	//FString PublisherName;
	// 게시 내용
	UPROPERTY(EditAnywhere)
	FString ContentString;

	void PrintStruct();
};
