// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "PlayerCharacter.h"
#include "Components/CanvasPanel.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/WidgetComponent.h"
#include "ReactionUI.h"
#include "Components/Image.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("2222222=========================================="));
	me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	ReactionComp = Cast<UReactionUI>(me->ReactionUIComponent->GetWidget());

	ReactionBar->SetVisibility(ESlateVisibility::Hidden);
	
	OpenReactionUI->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedOpenReactionUI);
	ClickReaction1->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction1);
	ClickReaction2->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction2);
	ClickReaction3->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction3);
	ClickReaction4->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction4);
	ClickReaction5->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction5);
	ClickReaction6->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction6);
	ClickReaction7->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction7);
	ClickReaction8->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction8);
	ClickReaction9->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction9);
	ClickReaction10->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction10);
	ClickReaction11->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction11);
	ClickReaction12->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction12);
	ClickReaction13->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction13);
	ClickReaction14->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedReaction14);

	PlayerStateBar->SetVisibility(ESlateVisibility::Hidden);

	OpenStateUI->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedOpenStateUI);
	ClickState1->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedState1);
	ClickState2->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedState2);
	ClickState3->OnClicked.AddDynamic(this, &UPlayerWidget::ClickedState3);
}

void UPlayerWidget::ClickedOpenReactionUI()
{
	if (ReactionBar->IsVisible()) {
		ReactionBar->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		ReactionBar->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerWidget::ClickedReaction1()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure1){
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure1);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
	// ReactionComp->ShowReaction(me->ReactionTexure1);
}

void UPlayerWidget::ClickedReaction2()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure2) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure2);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction3()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure3){
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure3);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction4()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure4) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure4);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction5()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure5) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure5);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction6()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure6) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure6);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction7()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure7) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure7);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction8()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure8) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure8);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction9()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure9) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure9);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction10()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure10) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure10);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction11()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure11) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure11);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction12()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure12) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure12);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction13()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure13) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure13);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::ClickedReaction14()
{
	if (ReactionComp && ReactionComp->Image2 && me->ReactionTexure14) {
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(me->ReactionTexure14);
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UPlayerWidget::HideImage, 3.0f, true);
	}
}

void UPlayerWidget::HideImage()
{
	ReactionComp->Image2->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::ClickedOpenStateUI()
{
	if (PlayerStateBar->IsVisible()) {
		PlayerStateBar->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		PlayerStateBar->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayerWidget::ClickedState1()
{
	me->SetCylinderMaterial(1);
}

void UPlayerWidget::ClickedState2()
{
	me->SetCylinderMaterial(2);
}

void UPlayerWidget::ClickedState3()
{
	me->SetCylinderMaterial(3);
}
