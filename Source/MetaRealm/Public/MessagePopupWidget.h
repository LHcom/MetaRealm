// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessagePopupWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UMessagePopupWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* txtMessage;
	UPROPERTY(meta=(BindWidget))
	class UButton* btnOK;

	UFUNCTION()
	void OnMyOkClick();
};
