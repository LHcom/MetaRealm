// Fill out your copyright notice in the Description page of Project Settings.


#include "Reaction_UserWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"



void UReaction_UserWidget::SetReactionImage()
{
	reactionCanvasPanel->SetVisibility(ESlateVisibility::Visible);
	reaction1->SetVisibility(ESlateVisibility::Hidden);
	reaction2->SetVisibility(ESlateVisibility::Hidden);
	reaction3->SetVisibility(ESlateVisibility::Hidden);
	reaction4->SetVisibility(ESlateVisibility::Hidden);
	reaction5->SetVisibility(ESlateVisibility::Hidden);
	reaction6->SetVisibility(ESlateVisibility::Hidden);
	reaction7->SetVisibility(ESlateVisibility::Hidden);
	reaction8->SetVisibility(ESlateVisibility::Hidden);
	reaction9->SetVisibility(ESlateVisibility::Hidden);
	reaction10->SetVisibility(ESlateVisibility::Hidden);
	reaction11->SetVisibility(ESlateVisibility::Hidden);
	reaction12->SetVisibility(ESlateVisibility::Hidden);
	reaction13->SetVisibility(ESlateVisibility::Hidden);
	reaction14->SetVisibility(ESlateVisibility::Hidden);
}

void UReaction_UserWidget::Callreaction1()
{
	if (!reaction1)
	{
		return;
	}
	reaction1->SetVisibility(ESlateVisibility::Visible);
}

void UReaction_UserWidget::Callreaction2()
{
	reaction2->SetVisibility(ESlateVisibility::Visible);
}

void UReaction_UserWidget::Callreaction3()
{
	reaction3->SetVisibility(ESlateVisibility::Visible);

}

void UReaction_UserWidget::Callreaction4()
{
	reaction4->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction5()
{
	reaction5->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction6()
{
	reaction6->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction7()
{
	reaction7->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction8()
{
	reaction8->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction9()
{
	reaction9->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction10()
{
	reaction10->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction11()
{
	reaction11->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction12()
{
	reaction12->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction13()
{
	reaction13->SetVisibility(ESlateVisibility::Visible);

}
void UReaction_UserWidget::Callreaction14()
{
	reaction14->SetVisibility(ESlateVisibility::Visible);
}
