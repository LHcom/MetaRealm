// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerList.h"
#include "UW_PlayerList.h"
#include "Components/ScrollBox.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "PlayerWidget.h"

void UMainPlayerList::AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget)
{
	if ( PlayListScrollBox && PlayerWidget )
	{
		PlayListScrollBox->AddChild(PlayerWidget);
	}
}
