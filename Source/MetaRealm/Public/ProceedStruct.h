// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProceedStruct.generated.h"

USTRUCT(Atomic,BlueprintType)
struct FProceedStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FString StrMemberList;
	UPROPERTY(EditAnywhere)
	FString StrMeetingTime;
	UPROPERTY(EditAnywhere)
	FString StrContent;
};
