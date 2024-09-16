// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowList.h"
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


void UWindowList::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonLookSharingScreen->OnClicked.AddDynamic(this, &UWindowList::OnButtonLookSharingScreen);
	ButtonWindowScreen->OnClicked.AddDynamic(this, &UWindowList::OnButtonWindowScreen);
	ImageSharingScreen->SetVisibility(ESlateVisibility::Hidden);
	ImageCoveringScreen->SetVisibility(ESlateVisibility::Hidden);
}

void UWindowList::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bStreaming && nullptr != ScreenActor)
	{
		ScreenActor->UpdateTexture();
	}
}

void UWindowList::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UWindowList::SetUserID(FString ID)
{
	ScreenActor->SetViewSharingUserID(ID);
}

void UWindowList::OnButtonWindowScreen()
{
	bStreaming = !bStreaming;
	FString streamID = "Editor";
	if (bStreaming)
	{
		TextWindowScreen->SetText(FText::FromString(TEXT("Sharing"))); //������

		ScreenActor->WindowScreenPlaneMesh->SetVisibility(true);
		//ScreenActor->BeginStreaming();
		// 1. PixelStreaming ����� �����ɴϴ�.
		IPixelStreamingModule* PixelStreamingModule = FModuleManager::Get().LoadModulePtr<IPixelStreamingModule>("PixelStreaming");
		//FModuleManager::GetModulePtr<IPixelStreamingModule>("PixelStreaming");

		if (PixelStreamingModule)
		{
			// ���� ������ ���̵� �����ͼ� Streamer�� �����Ѵ�.
			CurrentStreamer = PixelStreamingModule->FindStreamer(streamID);//GetCurrentSessionID());
			if (CurrentStreamer.IsValid())
			{
				{
					ScreenActor->UpdateTexture();

					//Back Buffer�� ���� �Է����� �����մϴ�.
					CurrentStreamer->SetInputHandlerType(EPixelStreamingInputType::RouteToWidget);

					UGameViewportClient* GameViewport = GEngine->GameViewport;
					ScreenActor->SceneCapture->Activate();


					// 2. Pixel Streaming ���� �Է����� ����
					VideoInput = FPixelStreamingVideoInputRenderTarget::Create(ScreenActor->SceneCapture->TextureTarget);

					CurrentStreamer->SetVideoInput(VideoInput); // ��Ʈ���ֿ� ���

					//Streamer->SetVideoInput(FPixelStreamingVideoInputViewport::Create(Streamer));
					CurrentStreamer->SetSignallingServerURL("ws://125.132.216.190:5678");

					//��Ʈ������ �����մϴ�.
					CurrentStreamer->StartStreaming();
				}

			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not find a valid streamer with the given ID."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PixelStreamingModule is not available."));
		}
	}
	else
	{
		TextWindowScreen->SetText(FText::FromString(TEXT("ȭ�����")));
		ScreenActor->WindowScreenPlaneMesh->SetVisibility(false);

		// 1. PixelStreaming ����� �����ɴϴ�.
		IPixelStreamingModule* PixelStreamingModule = FModuleManager::GetModulePtr<IPixelStreamingModule>("PixelStreaming");

		if (PixelStreamingModule)
		{
			// 2. ��Ʈ���Ӹ� �����ɴϴ�.
			TSharedPtr<IPixelStreamingStreamer> Streamer = PixelStreamingModule->FindStreamer(streamID);

			if (Streamer.IsValid())
			{
				// 4. ��Ʈ������ �����մϴ�.
				Streamer->StopStreaming();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not find a valid streamer with the given ID."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PixelStreamingModule is not available."));
		}
	}
}

void UWindowList::OnButtonLookSharingScreen()
{
	bLookStreaming = !bLookStreaming;
	if (bLookStreaming)
	{
		TextLookSharingScreen->SetText(FText::FromString(TEXT("See"))); //������
		ImageSharingScreen->SetVisibility(ESlateVisibility::Visible);
		//�������Ʈ subs
		ScreenActor->BeginLookSharingScreen();
		//ImageCoveringScreen->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TextLookSharingScreen->SetText(FText::FromString(TEXT("Screen Look"))); //ȭ�� ����
		ImageSharingScreen->SetVisibility(ESlateVisibility::Hidden);
		//�������Ʈ subs
		ScreenActor->StopLookSharingScreen();
		WindowList->ClearChildren();
		ImageCoveringScreen->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWindowList::SetScreenActor(AScreenActor* Actor)
{
	ScreenActor = Actor;
}

FString UWindowList::GetCurrentSessionID()
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// "GameSession"�� �⺻ ���� �̸��̸�, �ʿ信 ���� �ٸ� ���� �̸��� ����� �� ����
			FNamedOnlineSession* NamedSession = SessionInterface->GetNamedSession(NAME_GameSession);
			if (NamedSession)
			{
				// ���� ID ��������
				return NamedSession->GetSessionIdStr();
			}
		}
	}

	// ������ ���ų� �������� ������ ��
	return FString("No Session Found");
}

void UWindowList::InitSlot(TArray<FString> Items)
{
	// ���� ���� ����
	//SharingUserPanel->ClearChildren();
	//int32 Row = 0;
	//int32 Column = 0;


	//// ������ ������ �������� ���� ���� �� �߰�
	//for (FString UserID : Items)
	//{
	//	SharingUserSlot = CastChecked<USharingUserSlot>(CreateWidget(GetWorld(), SharingUserSlotFactory));
	//	if (SharingUserSlot)
	//	{
	//		// ���� ���ü� �� ���̾ƿ� Ȯ��
	//		SharingUserSlot->SetVisibility(ESlateVisibility::Visible);
	//		SharingUserSlot->SetUserID(UserID);
	//		//SharingUserSlot->FUserIDButtonDelegate_OneParam.BindUFunction(this, FName("SetUserID"));
	//		// Grid�� ���� �߰�
	//		SharingUserPanel->AddChildToUniformGrid(SharingUserSlot, Row, Column);

	//		// Row �� ����
	//		Row++;

	//		if (!SharingUserPanel)
	//		{
	//			UE_LOG(LogTemp, Error, TEXT("PartsPanel is not valid."));
	//			return;
	//		}

	//		//SharingUserSlot->clickcnt = P_clickcnt; // Ŭ�� �� ���� (��� InvSlot ���ŵż� clickcnt�� ������Ʈ �� �Ǵ� ���� ����)
	//	}
	//}
}

