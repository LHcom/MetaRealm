// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoWidget.h"

#include "PlayerCharacter.h"
#include "Components/EditableText.h"

void UMemoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->OnVisibilityChanged.AddDynamic(this, &UMemoWidget::OnMyVisibilityChanged);
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
			UE_LOG(LogTemp, Warning, TEXT("player is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player controller is nullptr"));
	}
}

void UMemoWidget::OnMyVisibilityChanged(ESlateVisibility newVisibility)
{
	if (newVisibility == ESlateVisibility::Visible)
		EditableText_0->SetText(FText::FromString(strMemo));
}

void UMemoWidget::setMemo(const FString& strContent)
{
	strMemo = strContent;
}
