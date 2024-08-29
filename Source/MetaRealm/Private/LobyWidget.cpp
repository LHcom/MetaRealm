// Fill out your copyright notice in the Description page of Project Settings.


#include "LobyWidget.h"

#include "NetGameInstance.h"

void ULobyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto GI = GetWorld()->GetGameInstance<UNetGameInstance>();
	if (GI)
	{
		GI->onSearchComplete.BindUObject(this, &ULobyWidget::OnFindSessionComplete);
	}
}

void ULobyWidget::OnFindSessionComplete(int32 index, FString sessionInfo)
{
	OnMyFindSessionSucceeded(index, sessionInfo);
}
