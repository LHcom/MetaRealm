// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobyWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API ULobyWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
public:
	 void OnFindSessionComplete(int32 index, FString sessionInfo);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMyFindSessionSucceeded(const int32& idx, const FString& sessionInfo);
};
