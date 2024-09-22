// Fill out your copyright notice in the Description page of Project Settings.


#include "EnterMeetingRoomUI.h"
#include "MR_Controller.h"
#include "Components/Button.h"
#include "NetGameInstance.h"

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
			if(auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()))
				mc->ServerMoveToMeetingRoomMap(gi->NickName);
			
			SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UEnterMeetingRoomUI::ButtonGoBackClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
