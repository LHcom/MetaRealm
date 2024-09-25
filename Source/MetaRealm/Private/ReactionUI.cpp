// Fill out your copyright notice in the Description page of Project Settings.


#include "ReactionUI.h"
#include "Components/Image.h"
#include "NetGameInstance.h"
#include "Components/TextBlock.h"
#include "PlayerCharacter.h"

void UReactionUI::NativeConstruct()
{
	Super::NativeConstruct();

}

void UReactionUI::ShowReaction(UTexture2D* ReactionImage)
{
	if (Image2) {
		Image2->SetBrushFromTexture(ReactionImage);
		Image2->SetVisibility(ESlateVisibility::Visible);

		GetWorld()->GetTimerManager().SetTimer(ReactionTimerHandle, this, &UReactionUI::HideReaction, 3.0f, false);
	}
}

void UReactionUI::HideReaction()
{
	Image2->SetVisibility(ESlateVisibility::Collapsed);
}
