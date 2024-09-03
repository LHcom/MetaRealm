// Fill out your copyright notice in the Description page of Project Settings.


#include "SignUpUI.h"
#include "Components/Button.h"

void USignUpUI::NativeConstruct()
{
	ButtonSignUp->OnClicked.AddDynamic(this, &USignUpUI::SignUpButtonClicked);
	ButtonExit->OnClicked.AddDynamic(this, &USignUpUI::ExitButtonClicked);
}

void USignUpUI::SignUpButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);

	// 나중에 사용할 코드
	/*if (PSEditable->GetText().ToString() != SecPSEditable->GetText().ToString()) {
		return;
	}
	TMap<FString, FString> SignUpData;
	SignUpData.Add("userId", IDEditable->GetText().ToString());
	SignUpData.Add("userPass", PSEditable->GetText().ToString());
	SignUpData.Add("userName", NameEditable->GetText().ToString());
	SignUpData.Add("birthday", BirthEditable->GetText().ToString());

	FString json = UJsonParseLib::MakeJson(SignUpData);
	FString SignUpURL = "http://192.168.1.40:8888/signup";
	LoginActor->ReqSignUpSuccess(SignUpURL, json);

	SetVisibility(ESlateVisibility::Hidden);
	LoginUI->SetVisibility(ESlateVisibility::Visible);*/
}

void USignUpUI::ExitButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}