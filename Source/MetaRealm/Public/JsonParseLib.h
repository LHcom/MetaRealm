// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <list>

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonParseLib.generated.h"

USTRUCT()
struct FUserInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString MSG;
	
	UPROPERTY(EditAnywhere)
	FString TkAddr;

	UPROPERTY(EditAnywhere)
	FString NickName;
};

/**
 * 
 */
UCLASS()
class METAREALM_API UJsonParseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Json 생성
	static FString MakeJson(const TMap<FString, FString>& source);
	// Json에서 데이터 추출
	static FString SignUpJsonParse(const FString& strJson);
	static FUserInfo LoginJsonParse(const FString& strJson);
	static FString SoundToTextJsonParse(const FString& strJson, FString& outStrMessage);
	static FString GenerateColorJsonParse(const FString& strJson);
};
