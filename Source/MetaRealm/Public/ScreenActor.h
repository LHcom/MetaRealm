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
	FCriticalSection CriticalSection; //다중 스레드에서 화면 캡처와 텍스쳐 업데이트 작업을 할때 데이터 경쟁을 방지하기 위함

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
	//============화면 공유===========

	/*cv::VideoCapture capture;
	cv::Mat image;

	UFUNCTION(BlueprintCallable)
	void ReadFrame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* imageTexture;
	UTexture2D* MatToTexture2D(const cv::Mat InMat);*/

	//cv::Mat GetScreenToCVMat(); //전체화면
	//cv::Mat GetWindowToCVMat(HWND hwnd); //특정 화면 공유

	//void LogActiveWindowTitles();

	//// 캡처할 특정 창의 핸들을 저장하는 변수
	//HWND TargetWindowHandle;

	//void FindTargetWindow();

	//// 창 제목을 저장할 변수 추가
	//TArray<FString> WindowTitles;

	//액터의 전반적인 위치 고정용
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "Components")
	class USceneComponent* sceneComp;

	void UpdateTexture(); //실시간 텍스쳐 업데이트

	class UMaterialInstanceDynamic* DynamicMaterial;

	UTexture2D* CaptureScreenToTexture();
	UTexture2D* CapturedTexture;

public:
	//=========픽셀 스트리밍 ===========
	// UPROPERTY(BlueprintReadWrite)
	// FString UserID; //픽셀 스트리밍 아이디
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite , Category = "Components")
	class UStaticMeshComponent* WindowScreenPlaneMesh; //픽셀 스트리밍 하는 Plane
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WindowListFactory;
	UPROPERTY(BlueprintReadWrite)
	class UWindowList* WindowList; //최종적으로 픽셀 스트리밍을 출력할 UI

	void SetViewSharingUserID(FString ID, const bool& bAddPlayer);

	//블루프린트 함수 호출
	void StopLookSharingScreen(); //스트리밍 중지
	void BeginStreaming(); //스트리밍 시작
	void BeginLookSharingScreen(); //스트리밍 공유

	void ChangeLookSharingScreen(); //스트리밍을 다른사람 시점으로 변경

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite , Category = "Capture")
	class UTextureRenderTarget2D* RenderTarget;
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Capture")
	class USceneCaptureComponent2D* SceneCapture;

	//==========화면공유 추가
	UPROPERTY()
	class AMetaRealmGameState* gs;
};
