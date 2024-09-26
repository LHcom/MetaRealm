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

	//// Steam ID를 가져오는 함수
	//FString GetSteamID() const;

	// MainUI 위젯 블루프린트 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UMainPlayerList> MainUIWidgetClass;

    // PlayerList 위젯 블루프린트 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUW_PlayerList> PlayerListWidgetClass;

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerList(const TArray<FString>& PlayerNames);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveToMeetingRoomMap(const FString& NickName);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastMoveToMeetingRoomMap(APlayerCharacter* PlayerCharacter);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerMoveToMainMap();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastMoveToMainMap(APlayerCharacter* PlayerCharacter);

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
	//-----------------------------------------게시판 관련
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MemoUIFactory;
	UPROPERTY(BlueprintReadWrite)
	class UMemoWidget* MemoUI;
	//------------------------------------------메세지 팝업
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMessagePopupWidget> MsgUIFactory;
	UPROPERTY(BlueprintReadWrite)
	class UMessagePopupWidget* MsgUI;
	//------------------------------------------플레이어 정보 기록
	void SetUserInfo(const FString& tkAdrr, const FString& nickName);

	//------------------------------------------화면 공유 UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> WindowListFactory;
	UPROPERTY(BlueprintReadWrite)
	class UWindowList* WindowListUI;

	 // 플레이어 이름 추가 함수
    UFUNCTION(Server , Reliable)
    void AddPlayerName(const FString& PlayerName);

	// ------------------------------------------플레이어 리스트
	UPROPERTY()
	class UMainPlayerList* MainUIWidget;

};
