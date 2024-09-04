// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BDVocieChatCharacter.generated.h"

UCLASS()
class METAREALM_API ABDVocieChatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABDVocieChatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	// VOIP Talker 컴포넌트를 선언합니다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Voice Chat", meta = (AllowPrivateAccess = "true"))
	class UVOIPTalker* VOIPTalkerComponent;

	// 마이크 임계값을 설정합니다.
	void SetMicThreshold(float Threshold);

	// 플레이어 상태에 등록합니다.
	void RegisterWithPlayerState();

	// 로컬 플레이어가 제어 중인지 확인합니다.
	bool IsLocallyControlled() const;

	// VOIP 관련 초기화 작업을 수행합니다.
	void InitializeVOIP();

	void SetUpNetworkVoice(); //StartNetworkVoice

	void StopVoice(); //StopNetworkVoice

};
