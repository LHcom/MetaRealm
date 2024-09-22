// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaRealmGameState.h"

#include "MetaRealm/MetaRealm.h"
#include "Net/UnrealNetwork.h"
#include "MR_Controller.h"
#include "EngineUtils.h"

void AMetaRealmGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMetaRealmGameState, gsContent);
	DOREPLIFETIME(AMetaRealmGameState, ArrRecordInfo);
	DOREPLIFETIME(AMetaRealmGameState , ConnectedPlayerNames);
	DOREPLIFETIME(AMetaRealmGameState , ConnectedPlayerStates);
}

void AMetaRealmGameState::HandleBeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::HandleBeginPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMetaRealmGameState::OnRep_ReplicatedHasBegunPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::OnRep_ReplicatedHasBegunPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMetaRealmGameState::OnRep_Proceeding()
{
	// 데이터 테이블에 내용을 추가한다.
	
	// 내용이 갱신되면 플레이어에게 알람을 보내준다.
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Add New Proceeding"));
	AB_LOG(LogABNetwork, Log, TEXT("Now Proceeding Count : %d"), ArrRecordInfo.Num());
}

//====================================================================================================

void AMetaRealmGameState::AddPlayerName(const FString& PlayerName)
{
	/*if ( !ConnectedPlayerNames.Contains(PlayerName) )
	{
		ConnectedPlayerNames.Add(PlayerName);
	}*/
	ConnectedPlayerNames.Add(PlayerName);
	ConnectedPlayerStates.Add(TEXT("접속중"));
	BroadcastPlayerList();
}

void AMetaRealmGameState::UpdatePlayerState(const FString& PlayerName , const FString& NewState)
{
	int32 PlayerIndex = ConnectedPlayerNames.IndexOfByKey(PlayerName);
	if ( PlayerIndex != INDEX_NONE )
	{
		ConnectedPlayerStates[PlayerIndex] = NewState;
		BroadcastPlayerList(); 
	}
}

void AMetaRealmGameState::BroadcastPlayerList()
{
	Multicast_UpdatePlayerList(ConnectedPlayerNames , ConnectedPlayerStates);
}

TArray<FString> AMetaRealmGameState::GetAllPlayerNames()
{
	return ConnectedPlayerNames;
}

TArray<FString> AMetaRealmGameState::GetAllPlayerStates()
{
	return ConnectedPlayerStates;
}

void AMetaRealmGameState::Multicast_UpdatePlayerList_Implementation(const TArray<FString>& PlayerNames , const TArray<FString>& PlayerStates)
{
	for ( AMR_Controller* Controller : TActorRange<AMR_Controller>(GetWorld()) )
	{
		if ( Controller )
		{
			Controller->UpdatePlayerList(PlayerNames , PlayerStates); 
		}
	}
}

