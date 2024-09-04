// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"
#include "Components/Button.h"
#include "LobyWidget.h"
#include "NetGameInstance.h"
#include "SignUpUI.h"

class UNetGameInstance;

void ULoginUI::NativeConstruct()
{
	ButtonLogin->OnClicked.AddDynamic(this, &ULoginUI::ButtonLoginClicked);
	ButtonSignUp->OnClicked.AddDynamic(this, &ULoginUI::ButtonSignUpClicked);
}

void ULoginUI::ButtonLoginClicked()
{
	// 로그인 정보를 체크하는 API 추가해야됌

	// LogIn Session
	auto GI = GetWorld()->GetGameInstance<UNetGameInstance>();
	if (GI)
	{
		GI->LogInSession();
	}
	
	// 나중에 변경할 내용
	//SetVisibility(ESlateVisibility::Hidden);
	//LobbyUI->SetVisibility(ESlateVisibility::Visible);
	
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
