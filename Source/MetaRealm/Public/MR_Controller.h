// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Templates/SubclassOf.h"
#include "UW_Main.h"
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

	// Steam ID¸¦ °¡Á®¿À´Â ÇÔ¼ö
	FString GetSteamID() const;

	// MainUI À§Á¬ ºí·çÇÁ¸°Æ® Å¬·¡½º
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUW_Main> MainUIWidgetClass;

    // PlayerList À§Á¬ ºí·çÇÁ¸°Æ® Å¬·¡½º
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUW_PlayerList> PlayerListWidgetClass;

	UFUNCTION()
	void ViewMainUI();

	UFUNCTION(BlueprintCallable)
	void MoveToMeetingRoomMap();
	
	UFUNCTION(BlueprintCallable)
	void MoveToMainMap();

	void SendMessage(const FText& Text);

	UFUNCTION()
	void FocusGame();

	UFUNCTION()
	void FocusChatInputText();

	UPROPERTY()
	class ACharacter* me;

private:
	UFUNCTION(Server, Unreliable)
	void CtoS_SendMessage(const FString& Message);

	UFUNCTION(Client, Unreliable)
	void StoC_SendMessage(const FString& Message);

	UPROPERTY()
	class AMetaRealmGM* gm;

public:
	//-----------------------------------------ê²Œì‹œ??ê´€??
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MemoUIFactory;
	UPROPERTY(BlueprintReadWrite)
	class UMemoWidget* MemoUI;
};
