// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UW_PlayerList.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UUW_PlayerList : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Name;

	void SetPlayerName(FString PlayerName);

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* State;

	void SetPlayerState(FString PlayerState);
};
