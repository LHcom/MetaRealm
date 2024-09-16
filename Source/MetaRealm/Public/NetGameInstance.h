// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "NetGameInstance.generated.h"

DECLARE_DELEGATE_TwoParams(FSearchComplete, int32, FString);

UCLASS()
class METAREALM_API UNetGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	// 세션 만드는 함수
	UFUNCTION(BlueprintCallable)
	void CreateMySession(FString roomName); // 방만들때 사용 (버튼 이벤트)
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	// 세션 파괴하는 함수
	UFUNCTION(BlueprintCallable)
	void DestroyMySession(bool bMakeSession = false); // 방 없앨때 사용 (서버 플레이어가 종료하면 호출)
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	// 세션을 검색 함수
	UFUNCTION(BlueprintCallable)
	void FindOtherSession(); // 방 찾을때
	void OnFindSessionComplete(bool bWasSuccessful);

	// 세션 참여 함수
	UFUNCTION(BlueprintCallable)
	void JoinOtherSession(int32 idx); // 방 입장
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result);

	// 방 나갈때 사용
	UFUNCTION(BlueprintCallable)
	void KickPlayer(APlayerController* PlayerToKick);


	FString StringBase64Encode(FString str);
	FString StringBase64Decode(FString str);


	// 이 변수통해 (세션 만들고, 세션 검색, 세션 참여)
	TSharedPtr<class IOnlineSession, ESPMode::ThreadSafe> sessionInterface;

	// 세션 검색에 쓰이는 클래스
	TSharedPtr<class FOnlineSessionSearch> sessionSearch;

	// 방 이름
	FString MyroomName = TEXT("METAREALM");
	// 세션 이름
	FString mySessionName = TEXT("MTVSMETAREALM");

	// 세션 검색이 완료되면 호출해야 하는 Delegate
	FSearchComplete onSearchComplete;

	//FString NowSession;

	UFUNCTION()
	void LogInSession();

	bool MakeSessionFlag = false;

	//=====================게시판 관련
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* DataTable;
	void SetBoardData(struct FBoardStruct newData);
	struct FBoardStruct GetBoardData();
	FString DT_RowName = "Board";
	void LoadBoardDT(UScriptStruct* RowStruct);
	bool SaveBoardDTToCSV();
	//=====================회의록 관련
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* ProceedDataTable;
	void SetProceedData(struct FProceedStruct newData);
	TArray<struct FProceedStruct> GetProceedData();
	void LoadProceedDT(UScriptStruct* RowStruct);
	bool SaveProceedDTToCSV();
	//=======================로그인
	UPROPERTY()
	FString TkAdrr;
	UPROPERTY()
	FString NickName;
};
