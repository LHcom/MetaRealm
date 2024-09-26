// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerList.h"

#include "MetaRealmGameState.h"
#include "MR_Controller.h"
#include "PlayerCharacter.h"
#include "UW_PlayerList.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "PlayerWidget.h"

void UMainPlayerList::NativeTick(const FGeometry& MyGeometry , float InDeltaTime)
{
	Super::NativeTick(MyGeometry , InDeltaTime);
}

void UMainPlayerList::NativeConstruct()
{
	Super::NativeConstruct();

	if (auto* Me = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		PC = Cast<AMR_Controller>(Me->GetController());
	}

	FTimerHandle hnd;
	GetWorld()->GetTimerManager().SetTimer(hnd, [&]()
	{
		if (PC)
		{
			if (auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()))
				PC->UpdatePlayerList(gs->ConnectedPlayerNames);
		}
	}, 1,true);
}

void UMainPlayerList::AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget)
{
	if (PlayListScrollBox && PlayerWidget)
	{
		PlayListScrollBox->AddChild(PlayerWidget);
	}
}
