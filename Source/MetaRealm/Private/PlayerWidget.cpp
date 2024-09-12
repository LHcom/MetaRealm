// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "PlayerCharacter.h"

void UPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
	
}

void UPlayerWidget::ClickedReaction2()
{

}

void UPlayerWidget::ClickedReaction3()
{

}

void UPlayerWidget::ClickedReaction4()
{

}

void UPlayerWidget::ClickedReaction5()
{

}

void UPlayerWidget::ClickedReaction6()
{

}

void UPlayerWidget::ClickedReaction7()
{

}

void UPlayerWidget::ClickedReaction8()
{

}

void UPlayerWidget::ClickedReaction9()
{

}

void UPlayerWidget::ClickedReaction10()
{

}

void UPlayerWidget::ClickedReaction11()
{

}

void UPlayerWidget::ClickedReaction12()
{

}

void UPlayerWidget::ClickedReaction13()
{

}

void UPlayerWidget::ClickedReaction14()
{

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
	
}

void UPlayerWidget::ClickedState2()
{
	
}

void UPlayerWidget::ClickedState3()
{
	
}
