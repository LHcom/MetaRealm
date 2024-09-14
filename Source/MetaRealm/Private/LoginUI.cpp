// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"

#include "JsonParseLib.h"
#include "Components/Button.h"
#include "LobyWidget.h"
#include "NetGameInstance.h"
#include "PlayerCharacter.h"
#include "SignUpUI.h"
#include "Components/EditableText.h"

class UNetGameInstance;

void ULoginUI::NativeConstruct()
{
	ButtonLogin->OnClicked.AddDynamic(this, &ULoginUI::ButtonLoginClicked);
	ButtonSignUp->OnClicked.AddDynamic(this, &ULoginUI::ButtonSignUpClicked);
	
	Me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ULoginUI::ButtonLoginClicked()
{
	// 로그인 정보를 체크하는 API 추가해야됌
	auto GI = GetWorld()->GetGameInstance<UNetGameInstance>();
	if (GI)
	{
		GI->LogInSession();
	}

	// if(!Me)
	// 	Me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//
	// FString id = IDEditable->GetText().ToString();
	// FString pw = PSEditable->GetText().ToString();
	//
	// if (id.IsEmpty())
	// {
	// 	// 아이디 미입력
	// 	return;
	// }
	// if (pw.IsEmpty())
	// {
	// 	// 패스워드 미입력
	// 	return;
	// }
	//
	// TMap<FString, FString> LoginData;
	// LoginData.Add("id", IDEditable->GetText().ToString());
	// LoginData.Add("pass", PSEditable->GetText().ToString());
	//
	// FString json = UJsonParseLib::MakeJson(LoginData);
	// Me->Login(json);
}

void ULoginUI::ButtonSignUpClicked()
{
	// SetVisibility(ESlateVisibility::Hidden);
	SignUpUI->SetVisibility(ESlateVisibility::Visible);
	
}
