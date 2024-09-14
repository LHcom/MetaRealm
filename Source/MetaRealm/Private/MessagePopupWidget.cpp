// Fill out your copyright notice in the Description page of Project Settings.


#include "MessagePopupWidget.h"

#include "PlayerCharacter.h"
#include "Components/Button.h"

void UMessagePopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btnOK->OnClicked.AddDynamic(this, &UMessagePopupWidget::OnMyOkClick);
}

void UMessagePopupWidget::OnMyOkClick()
{
	SetVisibility(ESlateVisibility::Hidden);
}
