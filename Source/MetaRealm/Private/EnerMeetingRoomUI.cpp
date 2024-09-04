// Fill out your copyright notice in the Description page of Project Settings.


#include "EnerMeetingRoomUI.h"
#include "Components/Button.h"
#include "MR_Controller.h"

void UEnerMeetingRoomUI::NativeConstruct()
{
	ButtonEnter->OnClicked.AddDynamic(this, &UEnerMeetingRoomUI::ButtonEnterClicked);
	ButtonGoBack->OnClicked.AddDynamic(this, &UEnerMeetingRoomUI::ButtonGoBackClicked);
	SetVisibility(ESlateVisibility::Hidden);
}

void UEnerMeetingRoomUI::ButtonEnterClicked()
{
	if (APlayerController* pc = GetOwningPlayer()) {
		AMR_Controller* mc = Cast<AMR_Controller>(pc);
		if (mc) {
			mc->MoveToMeetingRoomMap();
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UEnerMeetingRoomUI::ButtonGoBackClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
