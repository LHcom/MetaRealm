// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_HUD.h"
#include "MR_Controller.h"
#include "UW_Main.h"

AMain_HUD::AMain_HUD()
{
	static ConstructorHelpers::FClassFinder<UUW_Main> WB_Main(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/Chat/WB_Main.WB_Main_C'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void AMain_HUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // 시작하면 UI를 생성한다.
}

TSharedPtr<SWidget> AMain_HUD::GetChatInputTextObject()
{
	return MainUIObject->GetChatInputTextObject();
}

void AMain_HUD::AddChatMessage(const FString& Message)
{
	if (!CheckUIObject()) return;

	MainUIObject->AddChatMessage(Message);
}

bool AMain_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI가 없다면 생성.
	{
		return CreateUIObject();
	}
	return true; // 있다면 True.
}

bool AMain_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UUW_Main>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // 만들었다면 true.
		}
	}
	return false; // 못 만들었다면 false.
}