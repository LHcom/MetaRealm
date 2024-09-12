// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"

#include "PreOpenCVHeaders.h"
#include <opencv2/opencv.hpp>
#include "PostOpenCVHeaders.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HAL/CriticalSection.h"
#include "ScreenActor.generated.h"

UCLASS()
class METAREALM_API AScreenActor : public AActor
{
	GENERATED_BODY()
	FCriticalSection CriticalSection;
	
public:	
	// Sets default values for this actor's properties
	AScreenActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	FString MeetingMember = "";
	

};
