// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class METAREALM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class UReactionUI* ReactionComp;

	/*UPROPERTY()
	class * ReactionWidget;*/

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ProceedingFactory;

	UPROPERTY()
	class UProceedingWidget* ProceedingWidget = nullptr;

	void initProceedingUI();
	void ShowProceedingUI();

	FString GetSystemTime();
	FString MeetingStartTime;
	FString MeetingEndTime;

	FString GetMemberName();

	//-----------------------------------------게시판 관련
	UPROPERTY(BlueprintReadWrite)
	class UMemoWidget* MemoWidget;
	void initMemoUI();

	UFUNCTION(Server , Reliable)
	void ServerRPC_ContentSave(const FString& strContent); // 서버로 게시한 정보를 보내서 저장시킨다.
	UFUNCTION(NetMulticast , Reliable)
	void MulticastRPC_ContentSave(const FString& strContent); // 클라이언트에 게시판 정보를 보내고 기록 시킨다.
	//----------------------------------------------화면 공유 UI 관련
	UPROPERTY(BlueprintReadWrite)
	class UWindowList* WindowListWidget;
	void initWindowListUI();
	void ShowWindowListUI();
	void HideWindowListUI();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UWidgetComponent* PlayerUI;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	class UWidgetComponent* ReactionUIComponent;

	UFUNCTION(Server, Reliable)
	void ServerSetReaction(int32 ReactionIdx);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetReaction(int32 ReactionIdx);

	UFUNCTION()
	void ShowReaction(int32 ReactionIdx);

	UFUNCTION()
	void HideReaction();

	UFUNCTION()
	UTexture2D* GetReactionTextureFromId(int32 ReactionIdx);

	UPROPERTY(EditDefaultsOnly)
	class UMaterial* CharMat[6];

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CharMatFactory;

	UPROPERTY()
	class UCharacterCustomUI* CharMatWidget = nullptr;

	void initCharacterCustomUI();

	UFUNCTION(Server, Reliable)
	void ServerSetMeshMat(int32 value);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetMeshMat(int32 value);

	UFUNCTION()
	void SetMeshMat(int32 value);

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionArray[14];

	UPROPERTY(EditdefaultsOnly , BlueprintReadOnly)
	class UStaticMeshComponent* Cylinder;

	UPROPERTY(EditDefaultsOnly)
	class UMaterial* CylinderMaterial1;

	UPROPERTY(EditDefaultsOnly)
	class UMaterial* CylinderMaterial2;

	UPROPERTY(EditDefaultsOnly)
	class UMaterial* CylinderMaterial3;

	UFUNCTION()
	void SetCylinderMaterial(int32 value);

	UFUNCTION(Server , Reliable)
	void ServerSetCylinderMaterial(int32 value);

	UFUNCTION(NetMulticast , Reliable)
	void MulticastSetCylinderMaterial(int32 value);

private:
	//=================================로비
	UPROPERTY()
	class AHttpLib* HttpActor;

public:
	// 회원가입
	void SignUp(const FString& JSON);
	UFUNCTION()
	void getResSignUp(FString& ret);
	// 로그인
	void Login(const FString& JSON);
	UFUNCTION()
	void getResLogin(FString& ret);
	// 메세지 팝업UI
	UPROPERTY(BlueprintReadWrite)
	class UMessagePopupWidget* MsgWidget;
	void initMsgUI();

public:
	//==================================화면공유
	UFUNCTION(Server , Reliable)
	void ServerRPC_SetStreamingPlayer(const FString& PlayerID , const bool bAddPlayer);
	UFUNCTION(NetMulticast , Reliable)
	void Multicast_SetStreamingPlayer();
	// ========================================================= 보이스채팅
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAudioComponent* audioComp;
	// ==========================================플레이어 리스트
	void initPlayerUI();
	UPROPERTY()
	class UMainPlayerList* PlayerMainUI;
};
