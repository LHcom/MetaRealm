// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoWidget.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UMemoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UMemoWidget::setContent(const FString strContent)
{
	auto player = Cast<APlayerCharacter>(GetWorld()->GetFirstLocalPlayerFromController()->PlayerController->Player);
	if(player&&player->IsLocallyControlled())
	{
		player->ServerRPC_ContentSave(strContent); 
	}
}
