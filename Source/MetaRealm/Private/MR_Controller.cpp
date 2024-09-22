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


void AMR_Controller::PostInitializeComponents()
{
	AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("Begin"));
	Super::PostInitializeComponents();
	AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("End"));
}

void AMR_Controller::PostNetInit()
{
	AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("Begin"));
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if ( NetDriver )
	{
		if (NetDriver->ServerConnection)
			AB_LOG(LogABNetwork , Log , TEXT("Server Connection: %s") , *NetDriver->ServerConnection.GetName());
	}
	else
	{
		AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("No NetDriver"));
	}
	AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("End"));
}

void AMR_Controller::BeginPlay()
{
	AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("Begin"));
	Super::BeginPlay();
	me = GetWorld()->GetFirstPlayerController()->GetCharacter();
	gm = Cast<AMetaRealmGM>(GetWorld()->GetAuthGameMode());
	if ( gm )
	{
		AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("gm is not null"));
	}
	else
	{
		AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("gm is null"));
	}
	AB_LOG(LogABNetwork , Log , TEXT("%s") , TEXT("End"));

	FString CurrentMapName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if ( IsLocalController() )
	{
		if ( auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()) )
		{
			FBoardStruct currData = gi->GetBoardData();
			TArray<FProceedStruct> proceedData = gi->GetProceedData();
			FString PlayerName = gi->NickName;
			if ( auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()) )
			{
				UE_LOG(LogTemp , Warning , TEXT("Send Player Name : %s") , *PlayerName);
				gs->gsContent = currData.ContentString;
				gs->ArrRecordInfo = proceedData;
				AddPlayerName(PlayerName);
				//gs->BroadcastPlayerList();
			}
		}
	}
}

void AMR_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 액션 키 바인딩.
	InputComponent->BindAction(TEXT("Chat") , EInputEvent::IE_Pressed , this , &AMR_Controller::FocusChatInputText);
}

void AMR_Controller::UpdatePlayerList(const TArray<FString>& PlayerNames)
{
	if (UMainPlayerList* MainUIWidget = CreateWidget<UMainPlayerList>(this , MainUIWidgetClass))
	{
		MainUIWidget->AddToViewport();

		for (int32 i = 0; i < PlayerNames.Num(); i++)
		{
			if (UUW_PlayerList* PlayerListWidget = CreateWidget<UUW_PlayerList>(this , PlayerListWidgetClass))
			{
				FString pName , pState;
				if ( PlayerNames[i].Split("|" , &pName , &pState) )
				{
					PlayerListWidget->SetPlayerName(pName);
					PlayerListWidget->SetPlayerState(pState);
					MainUIWidget->AddPlayerToScrollBox(PlayerListWidget);
				}
			}
		}
	}
}

void AMR_Controller::ServerMoveToMeetingRoomMap_Implementation(const FString& NickName)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (!PlayerCharacter)
	{
		return;
	}
	if (gm)
	{
		UE_LOG(LogTemp , Warning , TEXT("Join Meeting Room Member : %s") , *NickName);

		if (gm->MeetingMember.IsEmpty())
			gm->MeetingMember = NickName;
		else
			gm->MeetingMember += "," + NickName;
	}

	MulticastMoveToMeetingRoomMap(PlayerCharacter);
}

void AMR_Controller::MulticastMoveToMeetingRoomMap_Implementation(APlayerCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
	{
		return;
	}

	TArray<AActor*> MeetingRoomActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld() , FName("MeetingRoom") , MeetingRoomActors);

	if (MeetingRoomActors.Num() > 0)
	{
		AActor* MeetingRoom = MeetingRoomActors[0];
		PlayerCharacter->SetActorLocation(MeetingRoom->GetActorLocation());
		PlayerCharacter->MeetingStartTime = PlayerCharacter->GetSystemTime();
	}
}

// void AMR_Controller::ServerRPC_SetProceedMember_Implementation(const FString& strMember)
// {
//
// }

void AMR_Controller::ServerMoveToMainMap_Implementation()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (!PlayerCharacter)
	{
		return;
	}
	MulticastMoveToMainMap(PlayerCharacter);

	// ClientTravel("/Game/KHH/KHH_TestMap/KHH_TESTMap", ETravelType::TRAVEL_Absolute, true);
}

void AMR_Controller::MulticastMoveToMainMap_Implementation(APlayerCharacter* PlayerCharacter)
{
	if (!PlayerCharacter)
	{
		return;
	}
	TArray<AActor*> MainMapActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld() , FName("MainRoom") , MainMapActors);

	if (MainMapActors.Num() > 0)
	{
		AActor* MainMap = MainMapActors[0];
		PlayerCharacter->SetActorLocation(MainMap->GetActorLocation());
		PlayerCharacter->MeetingEndTime = PlayerCharacter->GetSystemTime();
	}
}

void AMR_Controller::SendMessage(const FText& Text)
{
	FString PlayerName;
	if (auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()))
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
	if ( HUD == nullptr ) return;

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
}

void AMR_Controller::SetUserInfo(const FString& tkAdrr , const FString& nickName)
{
	if ( auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()) )
	{
		gi->TkAdrr = tkAdrr;
		gi->NickName = nickName;
	}
}

void AMR_Controller::AddPlayerName_Implementation(const FString& PlayerName)
{
	FString PlayerInfo = PlayerName + FString::Printf(TEXT("|접속중"));
	UE_LOG(LogTemp , Warning , TEXT("Player Name : %s") , *PlayerName);
	if ( auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()) ) {
		if ( !gs->ConnectedPlayerNames.Contains(PlayerInfo) )
		{
			gs->ConnectedPlayerNames.Add(PlayerInfo);
			if ( HasAuthority() )
			{

				gs->OnRep_ConnectedPlayerName();
			}
		}
	}

}

// 채팅 ==========================================================================================================
void AMR_Controller::CtoS_SendMessage_Implementation(const FString& Message)
{
	// 서버에서는 모든 PlayerController에게 이벤트를 보낸다.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld() , APlayerController::StaticClass() , OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMR_Controller* pc = Cast<AMR_Controller>(OutActor);
		if ( pc )
		{
			pc->StoC_SendMessage(Message);
		}
	}
}

void AMR_Controller::StoC_SendMessage_Implementation(const FString& Message)
{
	// 서버와 클라이언트는 이 이벤트를 받아서 실행한다.
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if ( HUD == nullptr ) return;

	HUD->AddChatMessage(Message);
}
