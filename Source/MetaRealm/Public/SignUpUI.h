// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SignUpUI.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API USignUpUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* IDEditable;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* PSEditable;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* SecPSEditable;

	UPROPERTY(meta=(BindWidget))
	class UEditableText* NickNameEditable;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonSignUp;

	UPROPERTY(meta=(BindWidget))
	class UButton* ButtonExit;

	UFUNCTION()
	void SignUpButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
};
