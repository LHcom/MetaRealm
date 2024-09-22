// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitMeetingRoomUI.h"
#include "Components/Button.h"
#include "MR_Controller.h"

void UExitMeetingRoomUI::NativeConstruct()
{
	ButtonExit->OnClicked.AddDynamic(this, &UExitMeetingRoomUI::ButtonExitClicked);
	ButtonGoBack->OnClicked.AddDynamic(this, &UExitMeetingRoomUI::ButtonGoBackClicked);
	SetVisibility(ESlateVisibility::Hidden);
}

void UExitMeetingRoomUI::ButtonExitClicked()
{
	if (APlayerController* pc = GetOwningPlayer()) {
		AMR_Controller* mc = Cast<AMR_Controller>(pc);
		if (mc) {
			mc->ServerMoveToMainMap();
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UExitMeetingRoomUI::ButtonGoBackClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
