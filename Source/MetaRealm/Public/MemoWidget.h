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
	//===========================Visible 속성 변경 이벤트에 바인딩할 함수
	UFUNCTION()
	void OnMyVisibilityChanged(ESlateVisibility newVisibility);
	//===========================컴포넌트 바인딩	
	UPROPERTY(meta=(BindWidget))
	class UButton* btnSave;
	UPROPERTY(meta=(BindWidget))
	class UButton* btnCancel;
	//===========================이벤트 바인딩 함수
	UFUNCTION()
	void OnMyClickSave();
	UFUNCTION()
	void OnMyClickCancel();
	//===========================저장 버튼 클릭시 호출될 함수
	UFUNCTION(BlueprintCallable)
	void setContent(const FString strContent);
public:
	UPROPERTY(meta=(BindWidget))
	class UEditableText* eTxtBoard;	
};
