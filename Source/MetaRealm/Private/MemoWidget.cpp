// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoWidget.h"

#include "PlayerCharacter.h"

void UMemoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMemoWidget::setContent(const FString strContent)
{
	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		auto player = Cast<APlayerCharacter>(pc->GetPawn());
		if (player && player->IsLocallyControlled())
		{
			player->ServerRPC_ContentSave(strContent);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("player is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("player controller is nullptr"));
	}
}
