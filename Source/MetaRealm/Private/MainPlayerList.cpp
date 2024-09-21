// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerList.h"
#include "UW_PlayerList.h"
#include "Components/ScrollBox.h"
#include "Components/Border.h"
#include "Components/Button.h"



void UMainPlayerList::NativeConstruct()
{
	Super::NativeConstruct();

	if ( PlayerList_btn )
	{
		PlayerList_btn->OnClicked.AddDynamic(this , &UMainPlayerList::VisiblePlayerList);
	}

	if ( PlayerList )
	{
		PlayerList->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMainPlayerList::VisiblePlayerList()
{
	if ( PlayerList )
	{
		if ( PlayerList->GetVisibility() == ESlateVisibility::Visible )
		{
			PlayerList->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			PlayerList->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UMainPlayerList::AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget)
{
	if ( PlayListScrollBox && PlayerWidget )
	{
		PlayListScrollBox->AddChild(PlayerWidget);
	}
}
