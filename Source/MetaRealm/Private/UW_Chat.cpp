// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Chat.h"
#include "MR_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"

void UUW_Chat::NativeConstruct()
{
	Super::NativeConstruct();
	if (ChatInputBox)
	{
		ChatInputBox->OnTextCommitted.AddDynamic(this, &UUW_Chat::OnChatTextCommitted);
	}
	ChatInputBox->SetIsEnabled(false);
}

void UUW_Chat::AddChatMessage(const FString& Message)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(Chat_ScrollBox);
	NewTextBlock->SetText(FText::FromString(Message));

	FSlateFontInfo FontInfo = NewTextBlock->GetFont();
	FontInfo.Size = 15;  
	NewTextBlock->SetFont(FontInfo);

	FSlateColor FontColor = FSlateColor(FLinearColor::Black);
	NewTextBlock->SetColorAndOpacity(FontColor);

	Chat_ScrollBox->AddChild(NewTextBlock);
	Chat_ScrollBox->ScrollToEnd();
}

void UUW_Chat::SetChatInputTextMessage(const FText& Text)
{
	ChatInputBox->SetText(Text);
}

TSharedPtr<SWidget> UUW_Chat::GetChatInputTextObject()
{
	return ChatInputBox->GetCachedWidget();
}

void UUW_Chat::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	AMR_Controller* MyPC = Cast<AMR_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MyPC == nullptr) return;

	switch (CommitMethod)
	{
	case ETextCommit::OnEnter:
		if (Text.IsEmpty() == false)
		{
			MyPC->SendMessage(Text); // 메시지 보냄.
			SetChatInputTextMessage(FText::GetEmpty()); // 메세지 전송했으니, 비워줌.
		}
		//MyPC->FocusGame(); // 다시 게임으로 
		//break;
		MyPC->FocusChatInputText(); // 다시 채팅창으로 
		break;
	case ETextCommit::OnCleared:
		MyPC->FocusGame(); // 다시 게임으로 포커싱.
		break;
	}
}