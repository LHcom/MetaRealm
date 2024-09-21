// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/BackgroundBlur.h"
#include "UW_PlayerList.h"
#include "UW_Main.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UUW_Main : public UUserWidget
{
	GENERATED_BODY()

public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);


	//virtual void NativeConstruct() override;

	UPROPERTY(Meta = (BindWidget))
	class UUW_Chat* UW_Chat;

	//UPROPERTY(Meta = (BindWidget))
	//class UButton* PlayerList_btn;

	//UPROPERTY(Meta = (BindWidget))
	//class UBorder* PlayerList;

	//UPROPERTY(Meta = (BindWidget))
	//class UScrollBox* PlayListScrollBox;

	//UFUNCTION()
	//void VisiblePlayerList();

	//void AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget);
};
