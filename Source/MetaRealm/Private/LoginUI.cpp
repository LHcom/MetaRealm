// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUI.h"

#include "JsonParseLib.h"
#include "Components/Button.h"
#include "LobyWidget.h"
#include "PlayerCharacter.h"
#include "SignUpUI.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

class UNetGameInstance;

void ULoginUI::NativeConstruct()
{
	ButtonLogin->OnClicked.AddDynamic(this , &ULoginUI::ButtonLoginClicked);
	ButtonSignUp->OnClicked.AddDynamic(this , &ULoginUI::ButtonSignUpClicked);

	Me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ULoginUI::ButtonLoginClicked()
{
	txtErrMsg->SetVisibility(ESlateVisibility::Hidden);
	txtErrMsg->SetText(FText::FromString(""));

	if ( !Me )
		Me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	FString id = IDEditable->GetText().ToString().TrimStartAndEnd();
	FString pw = PSEditable->GetText().ToString().TrimStartAndEnd();

	if ( id.IsEmpty() )
	{
		// 아이디 미입력
		FString ErrMsg = FString::Printf(TEXT("아이디를 입력해주시기 바랍니다."));
		ShowErrMsg(ErrMsg);
		return;
	}
	if ( pw.IsEmpty() )
	{
		// 패스워드 미입력
		FString ErrMsg = FString::Printf(TEXT("패스워드를 입력해주시기 바랍니다."));
		ShowErrMsg(ErrMsg);
		return;
	}

	TMap<FString , FString> LoginData;
	LoginData.Add("id" , IDEditable->GetText().ToString());
	LoginData.Add("pass" , PSEditable->GetText().ToString());

	FString json = UJsonParseLib::MakeJson(LoginData);
	Me->Login(json);
}

void ULoginUI::ButtonSignUpClicked()
{
	// SetVisibility(ESlateVisibility::Hidden);
	SignUpUI->SetVisibility(ESlateVisibility::Visible);

}

void ULoginUI::ShowErrMsg(FString& MSG)
{
	FString str = FString::Printf(TEXT("로그인 성공!!!"));

	if ( MSG.Equals(TEXT("Successes to login")) )
	{
		MSG = str;
		FLinearColor newColor(0,1,0,1);
		FSlateColor color(newColor);
		txtErrMsg->SetColorAndOpacity(color);
		ButtonLogin->SetIsEnabled(false);
		ButtonSignUp->SetIsEnabled(false);
		IDEditable->SetIsEnabled(false);
		PSEditable->SetIsEnabled(false);
	}
	txtErrMsg->SetText(FText::FromString(MSG));
	txtErrMsg->SetVisibility(ESlateVisibility::Visible);
}
