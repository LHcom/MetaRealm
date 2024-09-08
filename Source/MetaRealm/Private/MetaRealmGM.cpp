// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaRealmGM.h"

#include "MetaRealmGameState.h"
#include "MetaRealm/MetaRealm.h"
#include "MR_Controller.h"
#include "Main_HUD.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>
#include "Windows/HideWindowsPlatformTypes.h"


AMetaRealmGM::AMetaRealmGM()
{
	GameStateClass = AMetaRealmGameState::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AMR_Controller::StaticClass();
	HUDClass = AMain_HUD::StaticClass();
}

void AMetaRealmGM::BeginPlay()
{
	Super::BeginPlay();

	LogActiveWindowTitles();
}

void AMetaRealmGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 특정 창 핸들 찾기 (예: "ChatGPT - Chrome")
	FindTargetWindow();

	// 특정 창이 존재하면 그 창의 화면을 캡처
	if (TargetWindowHandle != nullptr)
	{
		// 특정 창의 화면을 캡처하고 텍스처로 변환
		cv::Mat windowImage = GetWindowToCVMat(TargetWindowHandle);
		imageTexture = MatToTexture2D(windowImage);
		UE_LOG(LogTemp, Warning, TEXT("Successfully captured the window: ChatGPT - Chrome"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target window not found. Capturing main screen instead."));
		// 타겟 창을 찾지 못한 경우 주 모니터 화면을 캡처
		//ReadFrame();  // 주 모니터 캡처 함수 호출
	}
}

void AMetaRealmGM::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
                            FString& ErrorMessage)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("===================================================="));
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	//ErrorMessage=TEXT("Server Is Full");

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

APlayerController* AMetaRealmGM::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal,
                                       const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId,
	                                                      ErrorMessage);
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
	return NewPlayerController;
}

void AMetaRealmGM::PostLogin(APlayerController* NewPlayer)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostLogin(NewPlayer);

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ClientConnections.Num() == 0)
		{
			AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No Client Connection"));
		}
		else
		{
			for (const auto& Connection : NetDriver->ClientConnections)
			{
				AB_LOG(LogABNetwork, Log, TEXT("Client Connection: %s"), *Connection.GetName());
			}
		}
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMetaRealmGM::StartPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::StartPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMetaRealmGM::ReadFrame()
{
	// 주 모니터 화면을 캡처하여 텍스처로 변환
	//cv::Mat desktopImage = GetScreenToCVMat();
	//imageTexture = MatToTexture2D(desktopImage);
}

UTexture2D* AMetaRealmGM::MatToTexture2D(const cv::Mat InMat)
{
	// 새로운 텍스처를 생성하고 설정
	UTexture2D* Texture = UTexture2D::CreateTransient(InMat.cols, InMat.rows, PF_B8G8R8A8);

	// 3채널 이미지를 BGRA로 변환한 후 텍스처에 복사
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
	// 4채널 이미지를 그대로 텍스처로 복사
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

	// 실패 시 반환
	Texture->PostEditChange();
	Texture->UpdateResource();
	return Texture;
}

cv::Mat AMetaRealmGM::GetScreenToCVMat()
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

cv::Mat AMetaRealmGM::GetWindowToCVMat(HWND hwnd)
{
	// 창의 전체 크기를 가져옴 (클라이언트 영역뿐 아니라 제목 표시줄, 테두리 포함)
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	HDC hWindowDC = GetDC(hwnd);
	HDC hMemoryDC = CreateCompatibleDC(hWindowDC);

	HBITMAP hBitmap = CreateCompatibleBitmap(hWindowDC, windowWidth, windowHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	// BitBlt를 통해 창의 전체 화면을 복사
	BitBlt(hMemoryDC, 0, 0, windowWidth, windowHeight, hWindowDC, 0, 0, SRCCOPY);
	SelectObject(hMemoryDC, hOldBitmap);

	// 캡처한 창을 OpenCV의 Mat로 변환
	cv::Mat windowImage(windowHeight, windowWidth, CV_8UC4);
	GetBitmapBits(hBitmap, windowImage.total() * windowImage.elemSize(), windowImage.data);

	UE_LOG(LogTemp, Warning, TEXT("GetWindowToCVMat Succed"));

	// 리소스 해제
	ReleaseDC(hwnd, hWindowDC);
	DeleteDC(hMemoryDC);
	DeleteObject(hBitmap);

	return windowImage;
}

void AMetaRealmGM::LogActiveWindowTitles()
{
	WindowTitles.Empty(); // 기존 리스트 비우기

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			int length = GetWindowTextLength(hwnd);
			if (length == 0)
				return true; // 창 타이틀이 없으면 무시

			if (!IsWindowVisible(hwnd))
				return true; // 보이지 않는 창 무시

			WINDOWPLACEMENT placement;
			placement.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hwnd, &placement);
			if (placement.showCmd == SW_SHOWMINIMIZED)
				return true; // 최소화된 창 무시

			LONG style = GetWindowLong(hwnd, GWL_STYLE);
			if (!(style & WS_OVERLAPPEDWINDOW))
				return true; // 일반 창이 아니면 무시

			TCHAR windowTitle[256];
			GetWindowText(hwnd, windowTitle, 256);

			// 창 제목을 배열에 추가
			TArray<FString>* WindowList = (TArray<FString>*)lParam;
			WindowList->Add(FString(windowTitle));

			return true;
		}, (LPARAM)&WindowTitles);

	UE_LOG(LogTemp, Log, TEXT("Window List Updated. Total Windows: %d"), WindowTitles.Num());
}

void AMetaRealmGM::FindTargetWindow()
{
	TargetWindowHandle = nullptr;  // 초기화

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			TCHAR windowTitle[256];
			GetWindowText(hwnd, windowTitle, 256);

			// "카카오톡" 창 찾기
			if (FString(windowTitle) == "MetaRealm - Microsoft Visual Studio")
			{
				HWND* targetHandle = (HWND*)lParam;
				*targetHandle = hwnd;
				return false;  // 창을 찾으면 열거 중지
			}

			return true;  // 창을 계속 열거
		}, (LPARAM)&TargetWindowHandle);

	if (TargetWindowHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target window not found"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Target window found: "));
	}
}
