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
	FCriticalSection CriticalSection; //���� �����忡�� ȭ�� ĸó�� �ؽ��� ������Ʈ �۾��� �Ҷ� ������ ������ �����ϱ� ����
	
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

	//============ȭ�� ����===========

	cv::VideoCapture capture;
	cv::Mat image;

	UFUNCTION(BlueprintCallable)
	void ReadFrame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* imageTexture;
	UTexture2D* MatToTexture2D(const cv::Mat InMat);

	class UMaterialInstanceDynamic* DynamicMaterial; 

	cv::Mat GetScreenToCVMat(); //��üȭ��
	cv::Mat GetWindowToCVMat(HWND hwnd); //Ư�� ȭ�� ����

	void LogActiveWindowTitles();

	// ĸó�� Ư�� â�� �ڵ��� �����ϴ� ����
	HWND TargetWindowHandle;

	void FindTargetWindow();

	// â ������ ������ ���� �߰�
	TArray<FString> WindowTitles;

	//������ �������� ��ġ ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class USceneComponent* sceneComp;

	void UpdateTexture(); //�ǽð� �ؽ��� ������Ʈ

public:
	//=========�ȼ� ��Ʈ���� ===========
	UPROPERTY(BlueprintReadWrite)
	FString UserID; //�ȼ� ��Ʈ���� ���̵�
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* WindowScreenPlaneMesh; //�ȼ� ��Ʈ���� �ϴ� Plane
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WindowListFactory;
	UPROPERTY(BlueprintReadWrite)
	class UWindowList* WindowList; //���������� �ȼ� ��Ʈ������ ����� UI

	void SetViewSharingUserID(FString ID);

	//�������Ʈ �Լ� ȣ��
	void StopLookSharingScreen(); //��Ʈ���� ����
	void BeginStreaming(); //��Ʈ���� ����
	void BeginLookSharingScreen(); //��Ʈ���� ����

	void ChangeLookSharingScreen(); //��Ʈ������ �ٸ���� �������� ����

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capture")
    class UTextureRenderTarget2D* RenderTarget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capture")
	class USceneCaptureComponent2D* SceneCapture;
	

};
