// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaRealmGameState.h"

#include "MetaRealm/MetaRealm.h"
#include "Net/UnrealNetwork.h"

void AMetaRealmGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMetaRealmGameState, gsContent);
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