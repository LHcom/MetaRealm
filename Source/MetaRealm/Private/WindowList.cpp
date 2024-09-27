// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowList.h"

#include "EngineUtils.h"
#include "NetGameInstance.h"
#include "PlayerCharacter.h"
#include "ScreenActor.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SceneCaptureComponent2D.h"
#include "../../../../Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/IPixelStreamingModule.h"
#include "../../../../Plugins/Media/PixelStreaming/Source/PixelStreamingInput/Public/PixelStreamingInputEnums.h"
#include "../../../../Plugins/Media/PixelStreaming/Source/PixelStreaming/Public/PixelStreamingVideoInputRenderTarget.h"

#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineSessionInterface.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSessionSettings.h"
#include "SharingUserSlot.h"
#include "Kismet/GameplayStatics.h"
#include "ProcessListButton.h"


void UWindowList::NativeConstruct()
{
	Super::NativeConstruct();

	// 레벨에 배치된 ScreenActor를 찾음
	for (TActorIterator<AScreenActor> It(GetWorld() , AScreenActor::StaticClass()); It; ++It)
	{
		ScreenActor = *It;
		break;
	}

	//ButtonLookSharingScreen->OnClicked.AddDynamic(this , &UWindowList::OnButtonLookSharingScreen);
	ButtonWindowScreen->OnClicked.AddDynamic(this , &UWindowList::OnButtonWindowScreen);
	ImageSharingScreen->SetVisibility(ESlateVisibility::Hidden);
	ImageCoveringScreen->SetVisibility(ESlateVisibility::Hidden);

	Me = Cast<APlayerCharacter>(GetOwningPlayerPawn());
	if (Me)
	{
		UE_LOG(LogTemp , Warning , TEXT("Me is not Null"));
		Me->WindowListWidget->TextWindowScreen->SetText(FText::FromString(TEXT("Screen Share")));
	}
	else
	{
		UE_LOG(LogTemp , Warning , TEXT("Me is NullPtr"));
	}
}

void UWindowList::NativeTick(const FGeometry& MyGeometry , float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
	if (bStreaming && nullptr != ScreenActor)
	{
		ScreenActor->UpdateTexture();
	}
}

void UWindowList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UWindowList::NativeDestruct()
{
	Super::NativeDestruct();

	if ( CurrentStreamer ) {
		CurrentStreamer->SetVideoInput(nullptr);
	}
}

void UWindowList::SetUserID(FString ID , const bool& bAddPlayer)
{
	ScreenActor->SetViewSharingUserID(ID , bAddPlayer);
}

void UWindowList::OnButtonWindowScreen()
{
	bStreaming = !bStreaming;
	//bStreaming = true;
	FString streamID; //유저아이디를 받아와서 streamID에 넣기
	
	if (bStreaming)
	{
		TextWindowScreen->SetText(FText::FromString(TEXT("Sharing"))); //공유중

		if (ScreenActor)
		{
			ScreenActor->WindowScreenPlaneMesh->SetVisibility(true);
			SetUserID(streamID , true);
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("ScreenActor nullptr"));
		}

		// 1. PixelStreaming 모듈을 가져옵니다.
		//IPixelStreamingModule* PixelStreamingModule = FModuleManager::Get().LoadModulePtr<IPixelStreamingModule>(
		//	"PixelStreaming");
		////FModuleManager::GetModulePtr<IPixelStreamingModule>("PixelStreaming");
		//if (PixelStreamingModule)
		//{
		//	// 현재 세션의 아이디를 가져와서 Streamer를 생성한다.
		//	CurrentStreamer = PixelStreamingModule->FindStreamer(streamID); //GetCurrentSessionID());
		//	if (CurrentStreamer.IsValid())
		//	{
		//		{
		//			ScreenActor->UpdateTexture();
		//			SetUserID(streamID, true); //스트리머 아이디 설정
		//			//Back Buffer를 비디오 입력으로 설정합니다.
		//			CurrentStreamer->SetInputHandlerType(EPixelStreamingInputType::RouteToWidget);

		//			UGameViewportClient* GameViewport = GEngine->GameViewport;
		//			ScreenActor->SceneCapture->Activate();


		//			// 2. Pixel Streaming 비디오 입력으로 설정
		//			VideoInput =
		//				FPixelStreamingVideoInputRenderTarget::Create(ScreenActor->SceneCapture->TextureTarget);

		//			CurrentStreamer->SetVideoInput(VideoInput); // 스트리밍에 사용

		//			//Streamer->SetVideoInput(FPixelStreamingVideoInputViewport::Create(Streamer));
		//			CurrentStreamer->SetSignallingServerURL("ws://125.132.216.190:5678");

		//			//스트리밍을 시작합니다.
		//			CurrentStreamer->StartStreaming();

		//			InitProcessListUI();
		//		}
		//	}
		//	else
		//	{
		//		UE_LOG(LogTemp , Error , TEXT("Could not find a valid streamer with the given ID."));
		//	}
		//}
		//else
		//{
		//	UE_LOG(LogTemp , Error , TEXT("PixelStreamingModule is not available."));
		//}
		streamID = GetCurrentSessionID(); //세션 아이디 받아오기

		IPixelStreamingModule& PixelStreamingModule1 = FModuleManager::LoadModuleChecked<IPixelStreamingModule>("PixelStreaming");
		CurrentStreamer = PixelStreamingModule1.CreateStreamer(streamID);
		if ( nullptr == CurrentStreamer )
			return;

		//ScreenActor에 CurrentStreamer 값 설정
		ScreenActor->CurrentStreamer = CurrentStreamer;
		//UserID로 StreamID 설정 (FString 타입)
		ScreenActor->UserID = streamID;


		//Back Buffer를 비디오 입력으로 설정합니다.
		CurrentStreamer->SetInputHandlerType(EPixelStreamingInputType::RouteToWidget);
		ScreenActor->SceneCapture->Activate();

		SetUserID(streamID, true);

		//InitProcessListUI(); //목록 받아오기

		// 2. Pixel Streaming 비디오 입력으로 설정
		VideoInput = FPixelStreamingVideoInputRenderTarget::Create(ScreenActor->SceneCapture->TextureTarget);
		CurrentStreamer->SetVideoInput(VideoInput); // 스트리밍에 사용
		CurrentStreamer->SetSignallingServerURL("ws://125.132.216.190:5678");
		CurrentStreamer->StartStreaming();
	}
	else
	{
		Me->WindowListWidget->TextWindowScreen->SetText(FText::FromString(TEXT("Screen Share"))); //화면 공유
		ScreenActor->WindowScreenPlaneMesh->SetVisibility(false);
		SetUserID(streamID , false);

		ProcessList->ClearChildren();
		
		//1. PixelStreaming 모듈을 가져옵니다.
		IPixelStreamingModule* PixelStreamingModule = FModuleManager::GetModulePtr<IPixelStreamingModule>(
			"PixelStreaming");

		if (PixelStreamingModule)
		{
			// 2. 스트리머를 가져옵니다.
			TSharedPtr<IPixelStreamingStreamer> Streamer = PixelStreamingModule->FindStreamer(streamID);

			if (Streamer.IsValid())
			{
				// 4. 스트리밍을 시작합니다.
				Streamer->StopStreaming();
			}
			else
			{
				UE_LOG(LogTemp , Error , TEXT("Could not find a valid streamer with the given ID."));
			}
		}
		else
		{
			UE_LOG(LogTemp , Error , TEXT("PixelStreamingModule is not available."));
		}
	}
}

//공유 받는 함수
void UWindowList::OnButtonLookSharingScreen()
{
	bLookStreaming = !bLookStreaming;
	if (bLookStreaming)
	{
		// 레벨에 배치된 ScreenActor를 찾음
		for ( TActorIterator<AScreenActor> It(GetWorld() , AScreenActor::StaticClass()); It; ++It )
		{
			ScreenActor = *It;
			break;
		}
		//TextLookSharingScreen->SetText(FText::FromString(TEXT("Watching"))); //보는중
		ImageSharingScreen->SetVisibility(ESlateVisibility::Visible);
		//블루프린트 subs
		//ScreenActor->BeginLookSharingScreen();
		ScreenActor->ChangeLookSharingScreen();
	}
	else
	{
		//TextLookSharingScreen->SetText(FText::FromString(TEXT("Screen Look"))); //화면 보기
		ImageSharingScreen->SetVisibility(ESlateVisibility::Hidden);
		//블루프린트 subs
		ScreenActor->StopLookSharingScreen();
		WindowList->ClearChildren();
		ProcessList->ClearChildren(); //프로세스 리스트 없애기
		ImageCoveringScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWindowList::SetScreenActor(AScreenActor* Actor)
{
	if (!Actor)
	{
		UE_LOG(LogTemp , Error , TEXT("Invalid ScreenActor passed to SetScreenActor"));
		return;
	}

	ScreenActor = Actor;
	UE_LOG(LogTemp , Log , TEXT("ScreenActor has been set successfully."));
}

FString UWindowList::GetCurrentSessionID()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// "GameSession"은 기본 세션 이름이며, 필요에 따라 다른 세션 이름을 사용할 수 있음
			FNamedOnlineSession* NamedSession = SessionInterface->GetNamedSession(NAME_GameSession);
			if (NamedSession)
			{
				// 세션 ID 가져오기
				return NamedSession->GetSessionIdStr();
			}
		}
	}

	// 세션이 없거나 가져오지 못했을 때
	return FString("No Session Found");
}

void UWindowList::InitSlot(TArray<FString> Items)
{
	// 기존 슬롯 제거
	WindowList->ClearChildren();
	int32 Row = 0;
	int32 Column = 0;


	// 아이템 데이터 바탕으로 슬롯 생성 및 추가
	for (FString UserID : Items)
	{
		SharingUserSlot = CastChecked<USharingUserSlot>(CreateWidget(GetWorld() , SharingUserSlotFactory));
		if (SharingUserSlot)
		{
			// 슬롯 가시성 및 레이아웃 확인
			SharingUserSlot->SetVisibility(ESlateVisibility::Visible);
			SharingUserSlot->SetUserID(UserID);
			//SharingUserSlot->FUserIDButtonDelegate_OneParam.BindUFunction(this, FName("SetUserID"));
			// Grid에 슬롯 추가
			WindowList->AddChildToUniformGrid(SharingUserSlot , Row , Column);

			// Row 값 증가
			Row++;

			if (!WindowList)
			{
				UE_LOG(LogTemp , Error , TEXT("PartsPanel is not valid."));
				return;
			}

			//SharingUserSlot->clickcnt = P_clickcnt; // 클릭 값 전달 (계속 InvSlot 갱신돼서 clickcnt값 업데이트 안 되는 문제 때문)
		}
	}
}

void UWindowList::InitProcessListUI()
{
	//기존 슬롯 제거
	ProcessList->ClearChildren();
	int32 Row = 0;
	int32 Column = 0;

	ScreenActor->LogActiveWindowTitles();

	//프로세스 리스트 추가, 윈도우 타이틀 배열의 수만큼 채우고 싶다.
	for( int i = 0; i < ScreenActor->WindowTitles.Num(); i++ ) {
		ProcessListButtonSlot = CastChecked<UProcessListButton>(CreateWidget(GetWorld() , ProcessListButtonFactory));

		if ( ProcessListButtonSlot ) {
			ProcessListButtonSlot->SetVisibility(ESlateVisibility::Visible);
			ProcessListButtonSlot->SetProcessList(ScreenActor->WindowTitles[i]);

			ProcessList->AddChildToUniformGrid(ProcessListButtonSlot , Row , Column);

			UE_LOG(LogTemp , Warning , TEXT("ProcessListButtonSlot Add"));
		}

		Row++;
	}
}
