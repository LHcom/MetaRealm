// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MetaRealmGameState.generated.h"

/**
 * 
 */
UCLASS()
class METAREALM_API AMetaRealmGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	virtual void HandleBeginPlay() override;
	virtual void OnRep_ReplicatedHasBegunPlay() override;

	// 게시판 내용을 저장할 변수
	UPROPERTY(Replicated)
	FString gsContent;
	
	// 회의실 내용을 리스트에 보관
	UPROPERTY(ReplicatedUsing=OnRep_Proceeding)
	TArray<struct FProceedStruct> ArrRecordInfo;

	UFUNCTION()
	void OnRep_Proceeding();

public:
	//=================화면공유
	UPROPERTY(BlueprintReadOnly , ReplicatedUsing=OnRep_StreamingID)
	TArray<FString> ArrStreamingUserID;
	UFUNCTION()
	void OnRep_StreamingID();

	//==================================================

	// 모든 접속된 플레이어의 이름 리스트를 저장하는 배열입니다.
    UPROPERTY(Replicated, BlueprintReadOnly)
    TArray<FString> ConnectedPlayerNames;

    // 플레이어 이름 추가 함수
    UFUNCTION(BlueprintCallable)
    void AddPlayerName(const FString& PlayerName);

    // 모든 플레이어의 리스트를 클라이언트에 전파하는 함수
    UFUNCTION(BlueprintCallable)
    void BroadcastPlayerList();

    // 모든 플레이어의 이름을 반환하는 함수
    UFUNCTION(BlueprintCallable)
    TArray<FString> GetAllPlayerNames();
    
    // 플레이어 이름 리스트가 변경되었을 때 호출되는 함수
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_UpdatePlayerList(const TArray<FString>& PlayerNames);
};
