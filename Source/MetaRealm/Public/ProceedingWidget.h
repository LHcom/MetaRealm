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

	UFUNCTION()
	void OnMyVisibilityChanged(ESlateVisibility InVisibility);

	UPROPERTY()
	class AMetaRealmGameState* GS;

	TArray<struct FProceedStruct> ArrRecordInfo;
	int32 totalPageNum;
	int32 CurrPageNum;

	void SetCurrPage(int32 newPageNum);
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_Member;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_Time;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_Condensation;

	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Close;
	//--------------------페이징
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Prev;
	UPROPERTY(meta = (BindWidget))
	class UButton* btn_Subs;
	UPROPERTY(meta = (BindWidget))
	class UEditableText* eTxt_PageNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* txt_TotalPageNum;

	UFUNCTION()
	void OnMyClickPrev();
	UFUNCTION()
	void OnMyClickSubs();
	UFUNCTION()
	void OnMyPageCommit(const FText& Text, ETextCommit::Type CommitMethod);
};
