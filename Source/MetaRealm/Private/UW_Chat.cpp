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
	// Text ������Ʈ�� �����ϰ�, ScrollBox�� �߰��Ѵ�.
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(Chat_ScrollBox);
	NewTextBlock->SetText(FText::FromString(Message));

	// �۾� ũ�⸦ �����ϱ� ���� ��Ʈ ������ �����Ѵ�.
	FSlateFontInfo FontInfo = NewTextBlock->Font;
	FontInfo.Size = 15;  
	NewTextBlock->SetFont(FontInfo);

	Chat_ScrollBox->AddChild(NewTextBlock);
	Chat_ScrollBox->ScrollToEnd(); // ���� �ֱ� ä���� ���� ����, ��ũ���� ���� �Ʒ��� ������.
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
			MyPC->SendMessage(Text); // �޽��� ����.
			SetChatInputTextMessage(FText::GetEmpty()); // �޼��� ����������, �����.
		}
		//MyPC->FocusGame(); // �ٽ� �������� 
		//break;
		MyPC->FocusChatInputText(); // �ٽ� ä��â���� 
		break;
	case ETextCommit::OnCleared:
		MyPC->FocusGame(); // �ٽ� �������� ��Ŀ��.
		break;
	}
}