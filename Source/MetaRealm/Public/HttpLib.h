// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include "HttpLib.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API AHttpLib : public AActor
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	UPROPERTY()
	class APlayerCharacter* player;	
private:
	const FString SignUpURL = ""; // 회원가입
	const FString LoginURL = ""; // 로그인
	const FString SoundToTextURL = "http://125.132.216.190:7777/v1/xr/stt"; // STT (회의 요약)
	//const FString SoundToTextURL = "http://218.155.101.24:7777/v1/xr/stt"; // STT (회의 요약)
	const FString GenerateColorURL = ""; // 캐릭터 머터리얼 색상 변경

	UPROPERTY()
	class AMetaRealmGM* gm;

public:
	void ReqSignUp(const FString& JSON);
	void OnResSignUp(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                 bool bConnectedSuccessfully);

	void ReqLogin(const FString& JSON);
	void OnResLogin(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable)
	void ReqSoundToText(const FString& FilePath);
	void OnResSoundToText(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                      bool bConnectedSuccessfully);

	void ReqGenerateColor(const FString& JSON);
	void OnResGenerateColor(FHttpRequestPtr Request, FHttpResponsePtr Response,
	                        bool bConnectedSuccessfully);

	
};
