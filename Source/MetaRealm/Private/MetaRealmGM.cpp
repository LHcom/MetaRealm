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

	// Ư�� â �ڵ� ã�� (��: "ChatGPT - Chrome")
	FindTargetWindow();

	// Ư�� â�� �����ϸ� �� â�� ȭ���� ĸó
	if (TargetWindowHandle != nullptr)
	{
		// Ư�� â�� ȭ���� ĸó�ϰ� �ؽ�ó�� ��ȯ
		cv::Mat windowImage = GetWindowToCVMat(TargetWindowHandle);
		imageTexture = MatToTexture2D(windowImage);
		UE_LOG(LogTemp, Warning, TEXT("Successfully captured the window: ChatGPT - Chrome"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target window not found. Capturing main screen instead."));
		// Ÿ�� â�� ã�� ���� ��� �� ����� ȭ���� ĸó
		//ReadFrame();  // �� ����� ĸó �Լ� ȣ��
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
	// �� ����� ȭ���� ĸó�Ͽ� �ؽ�ó�� ��ȯ
	//cv::Mat desktopImage = GetScreenToCVMat();
	//imageTexture = MatToTexture2D(desktopImage);
}

UTexture2D* AMetaRealmGM::MatToTexture2D(const cv::Mat InMat)
{
	// ���ο� �ؽ�ó�� �����ϰ� ����
	UTexture2D* Texture = UTexture2D::CreateTransient(InMat.cols, InMat.rows, PF_B8G8R8A8);

	// 3ä�� �̹����� BGRA�� ��ȯ�� �� �ؽ�ó�� ����
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
	// 4ä�� �̹����� �״�� �ؽ�ó�� ����
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

	// ���� �� ��ȯ
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
	// â�� ��ü ũ�⸦ ������ (Ŭ���̾�Ʈ ������ �ƴ϶� ���� ǥ����, �׵θ� ����)
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);

	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	HDC hWindowDC = GetDC(hwnd);
	HDC hMemoryDC = CreateCompatibleDC(hWindowDC);

	HBITMAP hBitmap = CreateCompatibleBitmap(hWindowDC, windowWidth, windowHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	// BitBlt�� ���� â�� ��ü ȭ���� ����
	BitBlt(hMemoryDC, 0, 0, windowWidth, windowHeight, hWindowDC, 0, 0, SRCCOPY);
	SelectObject(hMemoryDC, hOldBitmap);

	// ĸó�� â�� OpenCV�� Mat�� ��ȯ
	cv::Mat windowImage(windowHeight, windowWidth, CV_8UC4);
	GetBitmapBits(hBitmap, windowImage.total() * windowImage.elemSize(), windowImage.data);

	UE_LOG(LogTemp, Warning, TEXT("GetWindowToCVMat Succed"));

	// ���ҽ� ����
	ReleaseDC(hwnd, hWindowDC);
	DeleteDC(hMemoryDC);
	DeleteObject(hBitmap);

	return windowImage;
}

void AMetaRealmGM::LogActiveWindowTitles()
{
	WindowTitles.Empty(); // ���� ����Ʈ ����

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			int length = GetWindowTextLength(hwnd);
			if (length == 0)
				return true; // â Ÿ��Ʋ�� ������ ����

			if (!IsWindowVisible(hwnd))
				return true; // ������ �ʴ� â ����

			WINDOWPLACEMENT placement;
			placement.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(hwnd, &placement);
			if (placement.showCmd == SW_SHOWMINIMIZED)
				return true; // �ּ�ȭ�� â ����

			LONG style = GetWindowLong(hwnd, GWL_STYLE);
			if (!(style & WS_OVERLAPPEDWINDOW))
				return true; // �Ϲ� â�� �ƴϸ� ����

			TCHAR windowTitle[256];
			GetWindowText(hwnd, windowTitle, 256);

			// â ������ �迭�� �߰�
			TArray<FString>* WindowList = (TArray<FString>*)lParam;
			WindowList->Add(FString(windowTitle));

			return true;
		}, (LPARAM)&WindowTitles);

	UE_LOG(LogTemp, Log, TEXT("Window List Updated. Total Windows: %d"), WindowTitles.Num());
}

void AMetaRealmGM::FindTargetWindow()
{
	TargetWindowHandle = nullptr;  // �ʱ�ȭ

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
		{
			TCHAR windowTitle[256];
			GetWindowText(hwnd, windowTitle, 256);

			// "īī����" â ã��
			if (FString(windowTitle) == "MetaRealm - Microsoft Visual Studio")
			{
				HWND* targetHandle = (HWND*)lParam;
				*targetHandle = hwnd;
				return false;  // â�� ã���� ���� ����
			}

			return true;  // â�� ��� ����
		}, (LPARAM)&TargetWindowHandle);

	if (TargetWindowHandle == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Target window not found"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Target window found: "));
	}
}
