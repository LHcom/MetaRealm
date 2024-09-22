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
	UPROPERTY(ReplicatedUsing = OnRep_Proceeding)
	TArray<struct FProceedStruct> ArrRecordInfo;

	UFUNCTION()
	void OnRep_Proceeding();

	//==================================================

	UPROPERTY(Replicated , BlueprintReadOnly , ReplicatedUsing = OnRep_ConnectedPlayerName)
	TArray<FString> ConnectedPlayerNames;

	UFUNCTION()
	void OnRep_ConnectedPlayerName();


	// 플레이어 이름 추가 함수
	/*UFUNCTION(Server , Reliable)
	void AddPlayerName(const FString& PlayerName);*/

};

