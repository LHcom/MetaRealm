// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoWidget.h"

#include "MetaRealmGameState.h"
#include "PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

void UMemoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->OnVisibilityChanged.AddDynamic(this, &UMemoWidget::OnMyVisibilityChanged);
	btnSave->OnClicked.AddDynamic(this, &UMemoWidget::OnMyClickSave);
	btnCancel->OnClicked.AddDynamic(this, &UMemoWidget::OnMyClickCancel);
}

void UMemoWidget::OnMyVisibilityChanged(ESlateVisibility newVisibility)
{
	if (newVisibility == ESlateVisibility::Visible)
	{
		auto gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState());
		if (gs)
		{
			eTxtBoard->SetText(FText::FromString(gs->gsContent));
		}
	}
}

void UMemoWidget::OnMyClickSave()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	setContent(eTxtBoard->GetText().ToString());
}

void UMemoWidget::OnMyClickCancel()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UMemoWidget::setContent(const FString strContent)
{
	// 오너 플레이어 컨트롤러를 가져와서
	APlayerController* pc = GetOwningPlayer();
	if (pc)
	{
		// 로컬플레이어가 맞다면
		auto player = Cast<APlayerCharacter>(pc->GetPawn());
		if (player && player->IsLocallyControlled())
		{
			// 서버 RPC를 호출
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
