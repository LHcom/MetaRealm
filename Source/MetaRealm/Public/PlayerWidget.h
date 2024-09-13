// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;


	// ======================================================== Character Component Save Start
	
	UPROPERTY()
	class APlayerCharacter* me;

	UPROPERTY()
	class UReactionUI* ReactionComp;

	UPROPERTY()
	class UStaticMeshComponent* Cylinder;

	FTimerHandle handle;

	// ======================================================== Character Component Save End
	
	

	// ======================================================== Reaction Button Binding Start
	
	UPROPERTY(meta=(BindWidget))
	class UBorder* ReactionBar;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* OpenReactionUI;
	UFUNCTION()
	void ClickedOpenReactionUI();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction1;
	UFUNCTION()
	void ClickedReaction1();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction2;
	UFUNCTION()
	void ClickedReaction2();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction3;
	UFUNCTION()
	void ClickedReaction3();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction4;
	UFUNCTION()
	void ClickedReaction4();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction5;
	UFUNCTION()
	void ClickedReaction5();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction6;
	UFUNCTION()
	void ClickedReaction6();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction7;
	UFUNCTION()
	void ClickedReaction7();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction8;
	UFUNCTION()
	void ClickedReaction8();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction9;
	UFUNCTION()
	void ClickedReaction9();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction10;
	UFUNCTION()
	void ClickedReaction10();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction11;
	UFUNCTION()
	void ClickedReaction11();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction12;
	UFUNCTION()
	void ClickedReaction12();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction13;
	UFUNCTION()
	void ClickedReaction13();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ClickReaction14;
	UFUNCTION()
	void ClickedReaction14();

	UFUNCTION()
	void HideImage();
	// ======================================================== Reaction Button Binding End
	// 
	// ======================================================== State Button Binding Start

	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* PlayerStateBar;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* OpenStateUI;
	UFUNCTION()
	void ClickedOpenStateUI();

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* ClickState1;
	UFUNCTION()
	void ClickedState1();

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* ClickState2;
	UFUNCTION()
	void ClickedState2();

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* ClickState3;
	UFUNCTION()
	void ClickedState3();

	// ======================================================== State Button Binding Start
};
