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

	//auto* pc = Cast<AMR_Controller>(GetOwningPlayerController());
	//CheckUIObject(); // �����ϸ� UI�� �����Ѵ�.
	
}

TSharedPtr<SWidget> AMain_HUD::GetChatInputTextObject()
{
	auto* pc = Cast<AMR_Controller>(GetOwningPlayerController());
	return pc->MainUIWidget->GetChatInputTextObject();
}

void AMain_HUD::AddChatMessage(const FString& Message)
{
	// BeginPlay()�� ����Ǳ� ���� �� �Լ��� ���� ���� �� ���� �ִ�.
	// UI�� ����� ���� UI�� �����ϸ� ������ ���� ������ �˻��Ѵ�.
	//if (!CheckUIObject()) return;

	auto* pc = Cast<AMR_Controller>(GetOwningPlayerController());
	pc->MainUIWidget->AddChatMessage(Message);
}

//bool AMain_HUD::CheckUIObject()
//{
//	UE_LOG(LogTemp,Warning,TEXT("here"));
//	auto* pc = Cast<AMR_Controller>(GetOwningPlayerController());
//	if (pc->IsViewMainUI == false) // UI�� ���ٸ� ����.
//	{
//		return CreateUIObject();
//	}
//	return true; // �ִٸ� True.
//}
//
//bool AMain_HUD::CreateUIObject()
//{
//	if (MainUIClass)
//	{
//		MainUIObject = CreateWidget<UUW_Main>(GetOwningPlayerController(), MainUIClass);
//		if (MainUIObject)
//		{
//			MainUIObject->AddToViewport();
//			return true; // ������ٸ� true.
//		}
//	}
//	return false; // �� ������ٸ� false.
//}