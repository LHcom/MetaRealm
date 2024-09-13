// Fill out your copyright notice in the Description page of Project Settings.


#include "MR_Controller.h"
#include "MetaRealm/MetaRealm.h"
#include "Main_HUD.h"
#include "MetaRealmGM.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "Online/CoreOnline.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineIdentityInterface.h"
#include "GameFramework/Character.h"
#include "UW_Main.h"
#include "Blueprint/UserWidget.h"
#include "UW_PlayerList.h"

void AMR_Controller::PostInitializeComponents()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostInitializeComponents();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));

}

void AMR_Controller::PostNetInit()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
			AB_LOG(LogABNetwork, Log, TEXT("Server Connection: %s"), *NetDriver->ServerConnection.GetName());
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::BeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::BeginPlay();
	me = GetWorld()->GetFirstPlayerController()->GetCharacter();
	gm = Cast<AMetaRealmGM>(GetWorld()->GetAuthGameMode());
	if (gm)
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("gm is not null"));
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("gm is null"));
	}
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));

	FString CurrentMapName = UGameplayStatics::GetCurrentLevelName(GetWorld());

    if (CurrentMapName == "KHH_level") 
    {
        ViewMainUI();
    }
}

void AMR_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// �׼� Ű ���ε�.
	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMR_Controller::FocusChatInputText);
}

FString AMR_Controller::GetSteamID() const
{
	if (IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get())
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
		if (Identity.IsValid())
		{
			FUniqueNetIdRepl UniqueNetId = GetLocalPlayer()->GetPreferredUniqueNetId();
			if (UniqueNetId.IsValid())
			{
				return UniqueNetId->ToString();
			}
		}
	}
	return FString("Unknown");
}

void AMR_Controller::ViewMainUI()
{
	// MainUI 생성 및 표시
	if (UUW_Main* MainUIWidget = CreateWidget<UUW_Main>(this, MainUIWidgetClass))
	{
		MainUIWidget->AddToViewport();

		if (UUW_PlayerList* PlayerListWidget = CreateWidget<UUW_PlayerList>(this, PlayerListWidgetClass))
		{
			FString PlayerName = GetSteamID();
			PlayerListWidget->SetPlayerName(GetSteamID());

			// PlayerList 위젯을 ScrollBox에 추가
			MainUIWidget->AddPlayerToScrollBox(PlayerListWidget);
		}
	}

}

void AMR_Controller::MoveToMeetingRoomMap()
{
	TArray<AActor*> MeetingRoomActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MeetingRoom"), MeetingRoomActors);

	if (MeetingRoomActors.Num() > 0)
	{
		AActor* MeetingRoom = MeetingRoomActors[0];
		if (me)
		{
			me->SetActorLocation(MeetingRoom->GetActorLocation());
			auto player = CastChecked<APlayerCharacter>(me);
			if (player)
			{
				player->MeetingStartTime = player->GetSystemTime();

				if (gm)
				{
					if (gm->MeetingMember.IsEmpty())
						gm->MeetingMember = player->GetMemberName();
					else
						gm->MeetingMember += "," + player->GetMemberName();
				}
			}
		}
	}
	// ClientTravel("/Game/KSK/Maps/SK_MeetingRoomMap", ETravelType::TRAVEL_Absolute, true);
}

void AMR_Controller::MoveToMainMap()
{
	TArray<AActor*> MainMapActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MainRoom"), MainMapActors);

	if (MainMapActors.Num() > 0)
	{
		AActor* MainMap = MainMapActors[0];

		if (me)
		{
			me->SetActorLocation(MainMap->GetActorLocation());
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, "Move!", false);
			auto player = CastChecked<APlayerCharacter>(me);
			if (player)
				player->MeetingEndTime = player->GetSystemTime();
		}
	}
	// ClientTravel("/Game/KHH/KHH_TestMap/KHH_TESTMap", ETravelType::TRAVEL_Absolute, true);
}

void AMR_Controller::SendMessage(const FText& Text)
{
	// �¶��� ����ý��ۿ��� Identity �������̽��� ������
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
		if (Identity.IsValid())
		{
			// 0��° ���� �÷��̾��� ���� ID�� ������
			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);
			if (UserId.IsValid())
			{
				// ���� �г����� ������
				FString UserName = Identity->GetPlayerNickname(*UserId);
				FString Message = FString::Printf(TEXT("%s : %s"), *UserName, *Text.ToString());

				// ������ �޽����� ���� (CtoS_SendMessage ȣ��)
				CtoS_SendMessage(Message);
			}
		}
	}
}

void AMR_Controller::FocusGame()
{
	SetInputMode(FInputModeGameAndUI());
}

void AMR_Controller::FocusChatInputText()
{
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
}


void AMR_Controller::CtoS_SendMessage_Implementation(const FString& Message)
{
	// ���������� ��� PlayerController���� �̺�Ʈ�� ������.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMR_Controller* PC = Cast<AMR_Controller>(OutActor);
		if (PC)
		{
			PC->StoC_SendMessage(Message);
		}
	}
}

void AMR_Controller::StoC_SendMessage_Implementation(const FString& Message)
{
	// ������ Ŭ���̾�Ʈ�� �� �̺�Ʈ�� �޾Ƽ� �����Ѵ�.
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	HUD->AddChatMessage(Message);
}
