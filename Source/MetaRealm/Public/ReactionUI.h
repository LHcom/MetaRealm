// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReactionUI.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UReactionUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NickNameText;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image2;

	UFUNCTION()
	void ShowReaction(UTexture2D* ReactionImage);

	UFUNCTION()
	void HideReaction();

	FTimerHandle ReactionTimerHandle;
};
