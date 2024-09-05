// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Chat.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UUW_Chat : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
    
public:
	void AddChatMessage(const FString& Message);
	//FText GetChatInputTextMessage();
	void SetChatInputTextMessage(const FText& Text);
	TSharedPtr<class SWidget> GetChatInputTextObject(); // ���߿� Enter ������, ä�ÿ� ��Ŀ���ϱ� ���ؼ�.

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* Chat_ScrollBox;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* ChatInputBox;
    
private:
	
	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
};
