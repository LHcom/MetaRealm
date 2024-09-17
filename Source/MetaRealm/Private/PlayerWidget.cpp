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
#include "Components/TextBlock.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("2222222=========================================="));
	me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

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
	if ( me->HasAuthority() ) {
		me->ShowReaction(1);
	}
	else if (me->ReactionArray[0] ) {
		me->ServerSetReaction(1);
	}
}

void UPlayerWidget::ClickedReaction2()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(2);
	}
	else if ( me->ReactionArray[1] ) {
		me->ServerSetReaction(2);
	}
}

void UPlayerWidget::ClickedReaction3()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(3);
	}
	else if ( me->ReactionArray[2] ) {
		me->ServerSetReaction(3);
	}
}

void UPlayerWidget::ClickedReaction4()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(4);
	}
	else if ( me->ReactionArray[3] ) {
		me->ServerSetReaction(4);
	}
}

void UPlayerWidget::ClickedReaction5()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(5);
	}
	else if ( me->ReactionArray[4] ) {
		me->ServerSetReaction(5);
	}
}

void UPlayerWidget::ClickedReaction6()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(6);
	}
	else if ( me->ReactionArray[5] ) {
		me->ServerSetReaction(6);
	}
}

void UPlayerWidget::ClickedReaction7()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(7);
	}
	else if ( me->ReactionArray[6] ) {
		me->ServerSetReaction(7);
	}
}

void UPlayerWidget::ClickedReaction8()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(8);
	}
	else if ( me->ReactionArray[7] ) {
		me->ServerSetReaction(8);
	}
}

void UPlayerWidget::ClickedReaction9()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(9);
	}
	else if ( me->ReactionArray[8] ) {
		me->ServerSetReaction(9);
	}
}

void UPlayerWidget::ClickedReaction10()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(10);
	}
	else if ( me->ReactionArray[9] ) {
		me->ServerSetReaction(10);
	}
}

void UPlayerWidget::ClickedReaction11()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(11);
	}
	else if ( me->ReactionArray[10] ) {
		me->ServerSetReaction(11);
	}
}

void UPlayerWidget::ClickedReaction12()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(12);
	}
	else if ( me->ReactionArray[11] ) {
		me->ServerSetReaction(12);
	}
}

void UPlayerWidget::ClickedReaction13()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(13);
	}
	else if ( me->ReactionArray[12] ) {
		me->ServerSetReaction(13);
	}
}

void UPlayerWidget::ClickedReaction14()
{
	if ( me->HasAuthority() ) {
		me->ShowReaction(14);
	}
	else if ( me->ReactionArray[13] ) {
		me->ServerSetReaction(14);
	}
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
	me->ServerSetCylinderMaterial(1);
	FString tempStr = FString::Printf(TEXT("접속중"));
	StateText->SetText(FText::FromString(tempStr));
	StateText->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
	PlayerStateBar->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::ClickedState2()
{
	me->ServerSetCylinderMaterial(2);
	FString tempStr = FString::Printf(TEXT("집중모드"));
	StateText->SetText(FText::FromString(tempStr));
	StateText->SetColorAndOpacity(FSlateColor(FLinearColor::Red));
	PlayerStateBar->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerWidget::ClickedState3()
{
	me->ServerSetCylinderMaterial(3);
	FString tempStr = FString::Printf(TEXT("자리비움"));
	StateText->SetText(FText::FromString(tempStr));
	StateText->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
	PlayerStateBar->SetVisibility(ESlateVisibility::Hidden);
}
