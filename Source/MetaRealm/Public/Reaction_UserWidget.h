// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Reaction_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UReaction_UserWidget : public UUserWidget
{
	GENERATED_BODY()
public:


	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* reactionCanvasPanel;

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	class UImage* reaction1;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction2;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction3;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction4;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction5;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction6;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction7;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction8;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction9;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction10;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction11;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction12;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction13;

	UPROPERTY(meta=(BindWidget))
	class UImage* reaction14;


	UFUNCTION(BlueprintCallable)
	void SetReactionImage();

	UFUNCTION(BlueprintCallable)
	void Callreaction1();

	UFUNCTION(BlueprintCallable)
	void Callreaction2();

	UFUNCTION(BlueprintCallable)
	void Callreaction3();

	UFUNCTION(BlueprintCallable)
	void Callreaction4();

	UFUNCTION(BlueprintCallable)
	void Callreaction5();

	UFUNCTION(BlueprintCallable)
	void Callreaction6();

	UFUNCTION(BlueprintCallable)
	void Callreaction7();

	UFUNCTION(BlueprintCallable)
	void Callreaction8();

	UFUNCTION(BlueprintCallable)
	void Callreaction9();

	UFUNCTION(BlueprintCallable)
	void Callreaction10();

	UFUNCTION(BlueprintCallable)
	void Callreaction11();

	UFUNCTION(BlueprintCallable)
	void Callreaction12();

	UFUNCTION(BlueprintCallable)
	void Callreaction13();

	UFUNCTION(BlueprintCallable)
	void Callreaction14();

};
