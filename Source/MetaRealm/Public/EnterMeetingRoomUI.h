// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnterMeetingRoomUI.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UEnterMeetingRoomUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonEnter;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonGoBack;

	UFUNCTION(BlueprintCallable)
	void ButtonEnterClicked();

	UFUNCTION(BlueprintCallable)
	void ButtonGoBackClicked();
};
