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
private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
public:

	UPROPERTY(BlueprintReadWrite)
	class UPlayerWidget* PlayerListWidget;

	UPROPERTY(Meta = (BindWidget))
	class UBorder* PlayerList;

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* PlayListScrollBox;

	void AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget);

	UPROPERTY()
	class AMR_Controller* PC;
};
