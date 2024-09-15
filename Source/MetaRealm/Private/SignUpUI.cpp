// Fill out your copyright notice in the Description page of Project Settings.


#include "SignUpUI.h"

#include "JsonParseLib.h"
#include "PlayerCharacter.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

void USignUpUI::NativeConstruct()
{
	ButtonSignUp->OnClicked.AddDynamic(this, &USignUpUI::SignUpButtonClicked);
	ButtonExit->OnClicked.AddDynamic(this, &USignUpUI::ExitButtonClicked);

	Me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void USignUpUI::SignUpButtonClicked()
{
	if (!Me)
		Me = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!Me)
	{
		return;
	}

	FString id = IDEditable->GetText().ToString().TrimStartAndEnd();
	FString pw = PSEditable->GetText().ToString().TrimStartAndEnd();
	FString pwChk = SecPSEditable->GetText().ToString().TrimStartAndEnd();
	FString nickName = NickNameEditable->GetText().ToString().TrimStartAndEnd();

	if (id.IsEmpty())
	{
		// 아이디 미입력
		return;
	}
	if (pw.IsEmpty())
	{
		// 패스워드 미입력
		return;
	}
	if (pwChk.IsEmpty())
	{
		// 패스워드 확인 미입력
		return;
	}
	if (nickName.IsEmpty())
	{
		// 닉네임 확인 미입력
		return;
	}

	if (pw != pwChk)
	{
		// 패스워드 확인 불일치
		return;
	}

	TMap<FString, FString> SignUpData;
	SignUpData.Add("userId", id);
	SignUpData.Add("userPass", pw);
	SignUpData.Add("userName", nickName);
	SignUpData.Add("userEmail", "");
	SignUpData.Add("role", "USER");

	FString json = UJsonParseLib::MakeJson(SignUpData);
	Me->SignUp(json);
}

void USignUpUI::ExitButtonClicked()
{
	FString emptyText = "";
	IDEditable->SetText(FText::FromString(emptyText));
	PSEditable->SetText(FText::FromString(emptyText));
	SecPSEditable->SetText(FText::FromString(emptyText));
	NickNameEditable->SetText(FText::FromString(emptyText));
	SetVisibility(ESlateVisibility::Hidden);
}
