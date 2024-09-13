// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Main.h"
#include "UW_Chat.h"
#include "UW_PlayerList.h"
#include "Components/ScrollBox.h"


TSharedPtr<SWidget> UUW_Main::GetChatInputTextObject()
{
	return UW_Chat->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	UW_Chat->AddChatMessage(Message);
}

//================================================================

void UUW_Main::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerList_btn)
	{
		PlayerList_btn->OnClicked.AddDynamic(this, &UUW_Main::VisiblePlayerList);
	}

	if (PlayerList)
	{
		PlayerList->SetVisibility(ESlateVisibility::Visible);
	}
	if (PlayListScrollBox)
	{
		// ScrollBox �ʱ�ȭ ���� �߰�
		//PlayListScrollBox->ClearChildren();
	}
}

void UUW_Main::VisiblePlayerList()
{
	if (PlayerList)
	{
		if (PlayerList->IsVisible())
		{
			PlayerList->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			PlayerList->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UUW_Main::AddPlayerToScrollBox(UUW_PlayerList* PlayerWidget)
{
	if (PlayListScrollBox && PlayerWidget)
	{
		PlayListScrollBox->AddChild(PlayerWidget);
	}
}

