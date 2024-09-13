// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_PlayerList.h"

void UUW_PlayerList::NativeConstruct()
{
	Super::NativeConstruct();

}

void UUW_PlayerList::SetPlayerName(FString PlayerName)
{
    if (Name)
    {
        Name->SetText(FText::FromString(PlayerName));
    }
}

