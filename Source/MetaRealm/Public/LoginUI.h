// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUI.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API ULoginUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class USignUpUI* SignUpUI;

	UPROPERTY()
	class ULobyWidget* LobbyUI;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* IDEditable;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* PSEditable;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonLogin;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonSignUp;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* txtErrMsg;

	UFUNCTION()
	void ButtonLoginClicked();

	UFUNCTION()
	void ButtonSignUpClicked();

	void ShowErrMsg(FString& MSG);
	
private:
	//====================Lobby
	UPROPERTY()
	class APlayerCharacter* Me;
};
