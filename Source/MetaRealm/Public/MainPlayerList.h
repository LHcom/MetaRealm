// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_PlayerList.h"
#include "Components/ScrollBox.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "MainPlayerList.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UMainPlayerList : public UUserWidget
{
	GENERATED_BODY()

public:

	//virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite)
	class UPlayerWidget* PlayerListWidget;

	/*UPROPERTY(Meta = (BindWidget))
	class UButton* PlayerList_btn;*/

	UPROPERTY(Meta = (BindWidget))
	class UBorder* PlayerList;

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* PlayListScrollBox;

	//UFUNCTION()
	//void VisiblePlayerList();


	void AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget);

	
};
