// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceedingWidget.h"

#include "Components/Button.h"

void UProceedingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	btn_Close->OnClicked.AddDynamic(this,&UProceedingWidget::OnMyClose);
}

void UProceedingWidget::OnMyClose()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
