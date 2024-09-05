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
	TSharedPtr<class SWidget> GetChatInputTextObject(); // 나중에 Enter 누르면, 채팅에 포커싱하기 위해서.

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* Chat_ScrollBox;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* ChatInputBox;
    
private:
	
	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
};
