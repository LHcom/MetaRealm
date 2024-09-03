// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "SignUpUI.h"
#include "LobyWidget.h"

void ULoginUI::NativeConstruct()
{
	ButtonLogin->OnClicked.AddDynamic(this, &ULoginUI::ButtonLoginClicked);
	ButtonSignUp->OnClicked.AddDynamic(this, &ULoginUI::ButtonSignUpClicked);
}

void ULoginUI::ButtonLoginClicked()
{
	// ���߿� ������ ����
	SetVisibility(ESlateVisibility::Hidden);
	LobbyUI->SetVisibility(ESlateVisibility::Visible);
	
	// ������� ���߿� �� ����
	/*TMap<FString, FString> LoginData;
	LoginData.Add("id", IDEditable->GetText().ToString());
	LoginData.Add("pass", PSEditable->GetText().ToString());

	FString json = UJsonParseLib::MakeJson(LoginData);
	FString LoginURL = "url�� �� �ڸ�";
	LoginActor->ReqLoginSuccess(LoginURL, json);*/
}

void ULoginUI::ButtonSignUpClicked()
{
	// SetVisibility(ESlateVisibility::Hidden);
	SignUpUI->SetVisibility(ESlateVisibility::Visible);
}
