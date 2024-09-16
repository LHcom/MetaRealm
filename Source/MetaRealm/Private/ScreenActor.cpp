// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenActor.h"
#include "Engine/TextureRenderTarget2D.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"

//window viewer
#include "Components/StaticMeshComponent.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture2DDynamic.h"
#include <vector> 
#include "Styling/SlateBrush.h"
#include "Components/Image.h"
#include "Rendering/Texture2DResource.h"
#include "Kismet/KismetMathLibrary.h"
#include "WindowList.h"
#include "Engine/TextureRenderTarget2D.h"
#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "Components/SceneCaptureComponent2D.h"
#include "../../../../Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingStreamer.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
AScreenActor::AScreenActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("sceneComp"));
	SetRootComponent(sceneComp);

	//Plane Mesh 초기화
	WindowScreenPlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WindowScreenPlaneMesh"));
	//PlaneMesh->SetupAttachment(RootComponent);
	WindowScreenPlaneMesh->SetupAttachment(sceneComp);
	WindowScreenPlaneMesh->SetRelativeLocation(FVector(0, 0, 0));
	WindowScreenPlaneMesh->SetRelativeScale3D(FVector(3.00000, 10000, 1.000000));
	// 기본 Plane Mesh 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMeshAsset(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (PlaneMeshAsset.Succeeded())
	{
		WindowScreenPlaneMesh->SetStaticMesh(PlaneMeshAsset.Object);
	}
	// 기본 머티리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterial(TEXT("/Script/Engine.Material'/Game/XR_LSJ/WindowViewer/BasicShapeMaterial.BasicShapeMaterial'"));
	if (DefaultMaterial.Succeeded())
	{
		WindowScreenPlaneMesh->SetMaterial(0, DefaultMaterial.Object);
	}
	WindowScreenPlaneMesh->SetVisibility(false);


	RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("RenderTarget"));
	RenderTarget->CompressionSettings = TextureCompressionSettings::TC_Default;
	RenderTarget->SRGB = false;
	RenderTarget->bAutoGenerateMips = false;
	RenderTarget->bForceLinearGamma = true;
	RenderTarget->TargetGamma = 2.2f;
	RenderTarget->AddressX = TextureAddress::TA_Clamp;
	RenderTarget->AddressY = TextureAddress::TA_Clamp;
	RenderTarget->InitAutoFormat(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCapture->SetupAttachment(RootComponent);
	SceneCapture->CaptureSource = SCS_FinalColorLDR;
	SceneCapture->TextureTarget = RenderTarget;
}

// Called when the game starts or when spawned
void AScreenActor::BeginPlay()
{
	Super::BeginPlay();

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UCameraComponent* playerCamera = playerPawn->GetComponentByClass<UCameraComponent>();
	WindowScreenPlaneMesh->SetRelativeScale3D(FVector(3, 2, 1));
	sceneComp->AttachToComponent(playerCamera, FAttachmentTransformRules::SnapToTargetIncludingScale); //카메라 붙이기

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(sceneComp->GetComponentLocation(), playerCamera->GetComponentLocation());

	// Z 축이 카메라를 향하도록 회전
	DynamicMaterial = UMaterialInstanceDynamic::Create(WindowScreenPlaneMesh->GetMaterial(0), this);
	WindowScreenPlaneMesh->SetMaterial(0, DynamicMaterial);
	WindowList = Cast<UWindowList>(CreateWidget<UUserWidget>(GetWorld(), WindowListFactory));
	if (WindowList)
	{
		WindowList->AddToViewport(-1);
		WindowList->SetScreenActor(this);
	}
	
}

// Called every frame
void AScreenActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FindTargetWindow();

	UpdateTexture();
}

void AScreenActor::ReadFrame()
{
	cv::Mat desktopImage = GetScreenToCVMat();
	imageTexture = MatToTexture2D(desktopImage);
}

UTexture2D* AScreenActor::MatToTexture2D(const cv::Mat InMat)
{
	UTexture2D* Texture = UTexture2D::CreateTransient(InMat.cols, InMat.rows, PF_B8G8R8A8);

	if (InMat.type() == CV_8UC3)
	{
		cv::Mat bgraImage;
		cv::cvtColor(InMat, bgraImage, cv::COLOR_BGR2BGRA);

		FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
		void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(Data, bgraImage.data, bgraImage.total() * bgraImage.elemSize());
		Mip.BulkData.Unlock();
		Texture->PostEditChange();
		Texture->UpdateResource();
		return Texture;
	}
	else if (InMat.type() == CV_8UC4)
	{
		FTexture2DMipMap& Mip = Texture->GetPlatformData()->Mips[0];
		void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(Data, InMat.data, InMat.total() * InMat.elemSize());
		Mip.BulkData.Unlock();
		Texture->PostEditChange();
		Texture->UpdateResource();
		return Texture;
	}

	Texture->PostEditChange();
	Texture->UpdateResource();
	return Texture;
}

cv::Mat AScreenActor::GetScreenToCVMat()
{
	HDC hScreenDC = GetDC(NULL);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	int screenWidth = GetDeviceCaps(hScreenDC, HORZRES);
	int screenHeight = GetDeviceCaps(hScreenDC, VERTRES);

	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);
	BitBlt(hMemoryDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY);
	SelectObject(hMemoryDC, hOldBitmap);

	cv::Mat matImage(screenHeight, screenWidth, CV_8UC4);
	GetBitmapBits(hBitmap, matImage.total() * matImage.elemSize(), matImage.data);

	return matImage;
}

cv::Mat AScreenActor::GetWindowToCVMat(HWND hwnd)
{
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	HDC hWindowDC = GetDC(hwnd);
	HDC hMemoryDC = CreateCompatibleDC(hWindowDC);

	HBITMAP hBitmap = CreateCompatibleBitmap(hWindowDC, windowWidth, windowHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	BitBlt(hMemoryDC, 0, 0, windowWidth, windowHeight, hWindowDC, 0, 0, SRCCOPY);
	SelectObject(hMemoryDC, hOldBitmap);

	cv::Mat windowImage(windowHeight, windowWidth, CV_8UC4);
	GetBitmapBits(hBitmap, windowImage.total() * windowImage.elemSize(), windowImage.data);

	ReleaseDC(hwnd, hWindowDC);
	DeleteDC(hMemoryDC);
	DeleteObject(hBitmap);

	return windowImage;
}

//타이틀을 목록으로 출력
void AScreenActor::LogActiveWindowTitles()
{
	WindowTitles.Empty();

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			int length = GetWindowTextLength(hwnd);
			if (length == 0)
				return true; 

			if (!IsWindowVisible(hwnd))
				return true; 

			WINDOWPLACEMENT placement;
			placement.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hwnd, &placement);
			if (placement.showCmd == SW_SHOWMINIMIZED)
				return true; 

			LONG style = GetWindowLong(hwnd, GWL_STYLE);
			if (!(style & WS_OVERLAPPEDWINDOW))
				return true; 

			TCHAR windowTitle[256];
			GetWindowText(hwnd, windowTitle, 256);

			TArray<FString>* WindowList = (TArray<FString>*)lParam;
			WindowList->Add(FString(windowTitle));

			return true;
		}, (LPARAM)&WindowTitles);

}

void AScreenActor::FindTargetWindow()
{
	TargetWindowHandle = nullptr; 

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			TCHAR windowTitle[256];
			GetWindowText(hwnd, windowTitle, 256);

			// 비주얼 스튜디오를 찾음
			if (FString(windowTitle) == "MetaRealm - Microsoft Visual Studio")
			{
				HWND* targetHandle = (HWND*)lParam;
				*targetHandle = hwnd;
				return false;
			}

			return true; 
		}, (LPARAM)&TargetWindowHandle);

	if (TargetWindowHandle == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target window not found"));
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Target window found: "));
	}
}

void AScreenActor::UpdateTexture()
{
	if (TargetWindowHandle != nullptr)
	{
		//특정 앱만 찾아서 화면 공유
		cv::Mat windowImage = GetWindowToCVMat(TargetWindowHandle);
		imageTexture = MatToTexture2D(windowImage);
		//UE_LOG(LogTemp, Warning, TEXT("Successfully captured the window: ChatGPT - Chrome"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target window not found. Capturing main screen instead."));
		//ReadFrame(); 
	}
}

void AScreenActor::SetViewSharingUserID(FString ID)
{
	UserID = ID;
	ChangeLookSharingScreen();
}

void AScreenActor::StopLookSharingScreen()
{
	// 블루프린트 함수 이름
	FName FunctionName(TEXT("StopLookPixelStreaming")); // 블루프린트에서 정의한 함수명

	// 블루프린트 함수 가져오기
	UFunction* Function = FindFunction(FunctionName);

	if (Function)
	{
		// 블루프린트 함수 호출 (매개변수가 없는 경우)
		ProcessEvent(Function, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Function not found: %s"), *FunctionName.ToString());
	}
}

void AScreenActor::BeginStreaming()
{
	// 블루프린트 함수 이름
	FName FunctionName(TEXT("BeginStreaming")); // 블루프린트에서 정의한 함수명

	// 블루프린트 함수 가져오기
	UFunction* Function = FindFunction(FunctionName);

	if (Function)
	{
		// 블루프린트 함수 호출 (매개변수가 없는 경우)
		ProcessEvent(Function, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Function not found: %s"), *FunctionName.ToString());
	}
}

void AScreenActor::BeginLookSharingScreen()
{
	// 블루프린트 함수 이름
	FName FunctionName(TEXT("BeginLookPixelStreaming")); // 블루프린트에서 정의한 함수명

	// 블루프린트 함수 가져오기
	UFunction* Function = FindFunction(FunctionName);

	if (Function)
	{
		// 블루프린트 함수 호출 (매개변수가 없는 경우)
		ProcessEvent(Function, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Function not found: %s"), *FunctionName.ToString());
	}
}

void AScreenActor::ChangeLookSharingScreen()
{
	// 블루프린트 함수 이름
	FName FunctionName(TEXT("ChangeLookPixelStreaming")); // 블루프린트에서 정의한 함수명

	// 블루프린트 함수 가져오기
	UFunction* Function = FindFunction(FunctionName);

	if (Function)
	{
		// 블루프린트 함수 호출 (매개변수가 없는 경우)
		ProcessEvent(Function, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Function not found: %s"), *FunctionName.ToString());
	}
}

