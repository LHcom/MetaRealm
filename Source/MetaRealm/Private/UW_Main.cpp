// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Main.h"
#include "UW_Chat.h"


TSharedPtr<SWidget> UUW_Main::GetChatInputTextObject()
{
	return UW_Chat->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	UW_Chat->AddChatMessage(Message);
}