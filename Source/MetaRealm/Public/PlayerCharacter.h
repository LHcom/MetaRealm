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
	UFUNCTION()
	void setContent(const FString& strContent);
	//----------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UWidgetComponent* ReactionUIComponent;
	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly)
	class UStaticMeshComponent* Cylinder;
};
