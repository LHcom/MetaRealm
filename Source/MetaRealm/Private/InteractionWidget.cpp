// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionWidget.h"

#include "PlayerCharacter.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (!Me)
	{
		Me = Cast<APlayerCharacter>(GetOwningPlayerPawn());
		if (!Me)
		{
			UE_LOG(LogTemp, Warning, TEXT("Me Is Null"));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Me Is Not Null"));
	}
}
