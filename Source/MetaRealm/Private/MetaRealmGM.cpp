// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaRealmGM.h"

#include "MetaRealmGameState.h"
#include "MetaRealm/MetaRealm.h"
#include "MR_Controller.h"
#include "Main_HUD.h"
#include "GameFramework/Character.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineIdentityInterface.h"


AMetaRealmGM::AMetaRealmGM()
{
	GameStateClass = AMetaRealmGameState::StaticClass();

	DefaultPawnClass = ACharacter::StaticClass();
	PlayerControllerClass = AMR_Controller::StaticClass();
	HUDClass = AMain_HUD::StaticClass();
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

	// 스팀 ID 및 닉네임 가져오기
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
		if (Identity.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(NewPlayer->GetLocalPlayer()->GetControllerId());
			if (UserId.IsValid())
			{
				// 스팀 닉네임을 가져옴
				FString UserName = Identity->GetPlayerNickname(*UserId);
				FString JoinMessage = FString::Printf(TEXT("%s Join."), *UserName);

				// 모든 플레이어에게 알림 전송
				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
				{
					AMR_Controller* PC = Cast<AMR_Controller>(*It);
					if (PC)
					{
						PC->StoC_SendMessage_Implementation(JoinMessage);
					}
				}
			}
		}
	}

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMetaRealmGM::StartPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::StartPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}
