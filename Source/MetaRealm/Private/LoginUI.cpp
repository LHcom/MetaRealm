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
	// 나중에 변경할 내용
	SetVisibility(ESlateVisibility::Hidden);
	LobbyUI->SetVisibility(ESlateVisibility::Visible);
	
	// 여기부턴 나중에 쓸 내용
	/*TMap<FString, FString> LoginData;
	LoginData.Add("id", IDEditable->GetText().ToString());
	LoginData.Add("pass", PSEditable->GetText().ToString());

	FString json = UJsonParseLib::MakeJson(LoginData);
	FString LoginURL = "url이 들어갈 자리";
	LoginActor->ReqLoginSuccess(LoginURL, json);*/
}

void ULoginUI::ButtonSignUpClicked()
{
	// SetVisibility(ESlateVisibility::Hidden);
	SignUpUI->SetVisibility(ESlateVisibility::Visible);
}
