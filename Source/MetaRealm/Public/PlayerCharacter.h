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

	// ü��UI�� �����ؼ� �Ӹ����� ��ġ�ϰ�ʹ�.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UWidgetComponent* ReactionComp;

	/*UPROPERTY()
	class * ReactionWidget;*/

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ProceedingFactory;

	UPROPERTY()
	class UProceedingWidget* ProceedingWidget = nullptr;

	void initProceedingUI();
	void setTextProceedingUI(FString& strMember, FString& strTime, FString& strCondensation);

	FString GetSystemTime();
	FString MeetingStartTime;
	FString MeetingEndTime;

	FString GetMemberName();

	//-----------------------------------------게시판 관련
	// UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<class UUserWidget> MemoFactory;
	UPROPERTY(BlueprintReadWrite)
	class UMemoWidget* MemoWidget;
	void initMemoUI();
	
	UPROPERTY()
	class AActor* WhiteBoard;
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_ContentSave(const FString& strContent); // 서버로 게시한 정보를 보내서 저장시킨다.
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPC_ContentSave(const FString& strContent); // 클라이언트에 게시판 정보를 보내고 기록 시킨다.
	UFUNCTION(Client, Reliable)
	void ClientRPC_ContentSave(const FString& strContent); // 클라이언트에 게시판 정보를 보내고 기록 시킨다.

	//----------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UWidgetComponent* PlayerUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UWidgetComponent* ReactionUIComponent;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure1;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure2;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure3;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure4;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure5;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure6;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure7;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure8;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure9;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure10;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure11;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure12;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure13;

	UPROPERTY(EditDefaultsOnly)
	class UTexture2D* ReactionTexure14;


	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* Cylinder;
	
	UPROPERTY()
	class UMaterial* CylinderMaterial1;

	UPROPERTY()
	class UMaterial* CylinderMaterial2;
	
	UPROPERTY()
	class UMaterial* CylinderMaterial3;

	UFUNCTION()
	void SetCylinderMaterial(int32 value);
};
