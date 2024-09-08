// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"

#include "PreOpenCVHeaders.h"
#include <opencv2/opencv.hpp>
#include "PostOpenCVHeaders.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MetaRealmGM.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API AMetaRealmGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMetaRealmGM();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;

public:
	cv::VideoCapture capture;
	cv::Mat image;
	
	UFUNCTION(BlueprintCallable)
	void ReadFrame();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* imageTexture;
	UTexture2D* MatToTexture2D(const cv::Mat InMat);
	
	
	cv::Mat GetScreenToCVMat();
	cv::Mat GetWindowToCVMat(HWND hwnd);

	void LogActiveWindowTitles();

	// 캡처할 특정 창의 핸들을 저장하는 변수
	HWND TargetWindowHandle;

	void FindTargetWindow();

	// 창 제목을 저장할 변수 추가
	TArray<FString> WindowTitles;

};
