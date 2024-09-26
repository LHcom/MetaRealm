// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterCustomUI.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UCharacterCustomUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class APlayerCharacter* me;

	int32 value;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base_1;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base_2;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base_3;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base_4;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base_5;

	UPROPERTY(meta = (BindWidget))
	class UImage* Base_6;

	void SetHidden();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Red;
	UFUNCTION()
	void ClickedRed();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Blue;
	UFUNCTION()
	void ClickedBlue();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Green;
	UFUNCTION()
	void ClickedGreen();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Yellow;
	UFUNCTION()
	void ClickedYellow();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Pink;
	UFUNCTION()
	void ClickedPink();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* Purple;
	UFUNCTION()
	void ClickedPurple();

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	class UButton* ButtonSelect;
	UFUNCTION()
	void ClickedButtonSelect();
};
