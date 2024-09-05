// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_HUD.h"
#include "MR_Controller.h"
#include "UW_Main.h"

AMain_HUD::AMain_HUD()
{
	static ConstructorHelpers::FClassFinder<UUW_Main> WB_Main(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/Chat/WB_Main.WB_Main_C'"));
	if (WB_Main.Succeeded())
	{
		MainUIClass = WB_Main.Class;
	}
}

void AMain_HUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
}

TSharedPtr<SWidget> AMain_HUD::GetChatInputTextObject()
{
	return MainUIObject->GetChatInputTextObject();
}

void AMain_HUD::AddChatMessage(const FString& Message)
{
	// BeginPlay()�� ����Ǳ� ���� �� �Լ��� ���� ���� �� ���� �ִ�.
	// UI�� ����� ���� UI�� �����ϸ� ������ ���� ������ �˻��Ѵ�.
	if (!CheckUIObject()) return;

	MainUIObject->AddChatMessage(Message);
}

bool AMain_HUD::CheckUIObject()
{
	if (MainUIObject == nullptr) // UI�� ���ٸ� ����.
	{
		return CreateUIObject();
	}
	return true; // �ִٸ� True.
}

bool AMain_HUD::CreateUIObject()
{
	if (MainUIClass)
	{
		MainUIObject = CreateWidget<UUW_Main>(GetOwningPlayerController(), MainUIClass);
		if (MainUIObject)
		{
			MainUIObject->AddToViewport();
			return true; // ������ٸ� true.
		}
	}
	return false; // �� ������ٸ� false.
}