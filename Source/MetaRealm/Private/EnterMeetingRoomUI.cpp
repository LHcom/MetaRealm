// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterMeetingRoomUI.h"
#include "MR_Controller.h"
#include "Components/Button.h"

void UEnterMeetingRoomUI::NativeConstruct()
{
	ButtonEnter->OnClicked.AddDynamic(this, &UEnterMeetingRoomUI::ButtonEnterClicked);
	ButtonGoBack->OnClicked.AddDynamic(this, &UEnterMeetingRoomUI::ButtonGoBackClicked);
	SetVisibility(ESlateVisibility::Hidden);
}

void UEnterMeetingRoomUI::ButtonEnterClicked()
{
	if (APlayerController* pc = GetOwningPlayer()) {
		AMR_Controller* mc = Cast<AMR_Controller>(pc);
		if (mc) {
			mc->ServerMoveToMeetingRoomMap();
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UEnterMeetingRoomUI::ButtonGoBackClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
