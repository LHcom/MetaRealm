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

	FString id = IDEditable->GetText().ToString();
	FString pw = PSEditable->GetText().ToString();
	FString pwChk = SecPSEditable->GetText().ToString();
	FString nickName = NickNameEditable->GetText().ToString();

	if (id.IsEmpty())
	{
		// ���̵� ���Է�
		return;
	}
	if (pw.IsEmpty())
	{
		// �н����� ���Է�
		return;
	}
	if (pwChk.IsEmpty())
	{
		// �н����� Ȯ�� ���Է�
		return;
	}
	if (nickName.IsEmpty())
	{
		// �г��� Ȯ�� ���Է�
		return;
	}

	if (pw != pwChk)
	{
		// �н����� Ȯ�� ����ġ
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

	SetVisibility(ESlateVisibility::Hidden);
}

void USignUpUI::ExitButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
