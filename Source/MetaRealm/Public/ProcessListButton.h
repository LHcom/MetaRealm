// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProcessListButton.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UProcessListButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


public:
	 UPROPERTY(meta = (BindWidget))
    class UTextBlock* ProcessName;  // UserID를 표시하는 텍스트 블록

    UPROPERTY(meta = (BindWidget))
    class UButton* ChangeProcessButton;  // 사용자 ID 버튼

	class AScreenActor* ScreenActor;

public:
	//버튼 클릭 시 특정 화면으로 전환
	UFUNCTION()
	void OnChangeProcessButtonClicked();

	//버튼 텍스트 이름 변경 
	UFUNCTION()
	void SetProcessList(FString ProgramName);
	
};
