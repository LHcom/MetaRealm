// Fill out your copyright notice in the Description page of Project Settings.


#include "MR_Controller.h"

#include "BoardStruct.h"
#include "ProceedStruct.h"
#include "MetaRealm/MetaRealm.h"
#include "Main_HUD.h"
#include "MetaRealmGameState.h"
#include "MetaRealmGM.h"
#include "NetGameInstance.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "Online/CoreOnline.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineIdentityInterface.h"
#include "GameFramework/Character.h"
#include "UW_Main.h"
#include "Blueprint/UserWidget.h"
#include "UW_PlayerList.h"
#include "MainPlayerList.h"
#include "NetGameInstance.h"


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
		//ViewMainUI();
	}

	if (auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()))
	{
		FBoardStruct currData = gi->GetBoardData();
		TArray<FProceedStruct> proceedData = gi->GetProceedData();
		if (auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()))
		{
			gs->gsContent = currData.ContentString;
			gs->ArrRecordInfo = proceedData;
		}
	}
	if ( auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()) )
	{
		FString PlayerName = gi->NickName;
		if ( auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()) )
		{
			gs->AddPlayerName(PlayerName);
			gs->BroadcastPlayerList();
		}
	}
}

void AMR_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 액션 키 바인딩.
	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMR_Controller::FocusChatInputText);
}

void AMR_Controller::ViewMainUI()
{
	if ( UMainPlayerList* MainUIWidget = CreateWidget<UMainPlayerList>(this , MainUIWidgetClass) )
	{
		MainUIWidget->AddToViewport();

		if ( auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()) )
		{
			TArray<FString> PlayerNames = gs->GetAllPlayerNames();
			TArray<FString> PlayerStates = gs->GetAllPlayerStates();

			for ( int32 i = 0; i < PlayerNames.Num(); i++ )
			{
				if ( UUW_PlayerList* PlayerListWidget = CreateWidget<UUW_PlayerList>(this , PlayerListWidgetClass) )
				{
					PlayerListWidget->SetPlayerName(PlayerNames[i]);
					PlayerListWidget->SetPlayerState(PlayerStates[i]);
					MainUIWidget->AddPlayerToScrollBox(PlayerListWidget);
				}
			}
		}
	}
}

void AMR_Controller::UpdatePlayerList(const TArray<FString>& PlayerNames , const TArray<FString>& PlayerStates)
{
	if ( UMainPlayerList* MainUIWidget = CreateWidget<UMainPlayerList>(this , MainUIWidgetClass) )
	{
		MainUIWidget->AddToViewport();

		for ( int32 i = 0; i < PlayerNames.Num(); i++ )
		{
			if ( UUW_PlayerList* PlayerListWidget = CreateWidget<UUW_PlayerList>(this , PlayerListWidgetClass) )
			{
				PlayerListWidget->SetPlayerName(PlayerNames[i]);
				PlayerListWidget->SetPlayerState(PlayerStates[i]);
				MainUIWidget->AddPlayerToScrollBox(PlayerListWidget);
			}
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
	FString PlayerName;
	if ( auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()) )
	{
		PlayerName = gi->NickName;
	}
	FString Message = FString::Printf(TEXT("%s : %s") , *PlayerName , *Text.ToString());

	// 서버로 메시지를 전송 (CtoS_SendMessage 호출)
	CtoS_SendMessage(Message);
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

void AMR_Controller::SetUserInfo(const FString& tkAdrr, const FString& nickName)
{
	if (auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()))
	{
		gi->TkAdrr = tkAdrr;
		gi->NickName = nickName;
	}
}


void AMR_Controller::CtoS_SendMessage_Implementation(const FString& Message)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMR_Controller* pc = Cast<AMR_Controller>(OutActor);
		if (pc)
		{
			pc->StoC_SendMessage(Message);
		}
	}
}

void AMR_Controller::StoC_SendMessage_Implementation(const FString& Message)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	HUD->AddChatMessage(Message);
}
