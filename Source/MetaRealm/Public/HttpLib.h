// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpLib.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UHttpLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	const FString SignUpURL = ""; // 회원가입
	const FString LoginURL = ""; // 로그인
	const FString SoundToTextURL = ""; // STT (회의 요약)
	const FString GenerateColorURL = ""; // 캐릭터 머터리얼 색상 변경

public:
	void ReqSignUp(const FString& JSON);
	void OnResSignUp(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                 bool bConnectedSuccessfully);

	void ReqLogin(const FString& JSON);
	void OnResLogin(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                bool bConnectedSuccessfully);

	void ReqSoundToText(const FString& JSON);
	void OnResSoundToText(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                      bool bConnectedSuccessfully);

	void ReqGenerateColor(const FString& JSON);
	void OnResGenerateColor(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                        bool bConnectedSuccessfully);
};
