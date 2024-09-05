// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MR_Controller.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API AMR_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
	virtual void PostNetInit() override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


	UFUNCTION(BlueprintCallable)
	void MoveToMeetingRoomMap();
	
	UFUNCTION(BlueprintCallable)
	void MoveToMainMap();

	void SendMessage(const FText& Text);

	UFUNCTION()
	void FocusGame();

	UFUNCTION()
	void FocusChatInputText();

private:
	UFUNCTION(Server, Unreliable)
	void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client, Unreliable)
	void StoC_SendMessage(const FString& Message);
};
