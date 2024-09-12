// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MemoWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UMemoWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void setContent(const FString strContent);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString strMemo;

	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, EditDefaultsOnly)
	class UEditableText* EditableText_0;

	void setMemo(const FString& strContent);
};
