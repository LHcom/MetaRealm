// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProceedingWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UProceedingWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnMyClose();
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_Member;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_Time;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_Condensation;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Close;

	
};
