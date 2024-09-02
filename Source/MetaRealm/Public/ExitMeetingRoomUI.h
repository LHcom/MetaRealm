// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExitMeetingRoomUI.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UExitMeetingRoomUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonExit;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonGoBack;

	UFUNCTION(BlueprintCallable)
	void ButtonExitClicked();

	UFUNCTION(BlueprintCallable)
	void ButtonGoBackClicked();
};
