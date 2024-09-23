// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SharingUserSlot.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API USharingUserSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* UserIDText;  // UserID를 표시하는 텍스트 블록

    UPROPERTY(meta = (BindWidget))
    class UButton* UserIDButton;  // 사용자 ID 버튼

    // UserID를 설정하는 함수
    UFUNCTION(BlueprintCallable)
    void SetUserID(FString ID);

    // 해당 사용자에 대한 ID 저장
    FString CurrentUserID;

    // 사용자 ID 버튼 클릭 시 호출될 함수
    UFUNCTION()
    void OnUserIDButtonClicked();
	
};
