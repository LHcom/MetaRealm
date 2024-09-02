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

	// VOIP Talker ������Ʈ�� �����մϴ�.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Voice Chat", meta = (AllowPrivateAccess = "true"))
	class UVOIPTalker* VOIPTalkerComponent;

	// ����ũ �Ӱ谪�� �����մϴ�.
	void SetMicThreshold(float Threshold);

	// �÷��̾� ���¿� ����մϴ�.
	void RegisterWithPlayerState();

	// ���� �÷��̾ ���� ������ Ȯ���մϴ�.
	bool IsLocallyControlled() const;

	// VOIP ���� �ʱ�ȭ �۾��� �����մϴ�.
	void InitializeVOIP();

	void SetUpNetworkVoice(); //StartNetworkVoice

	void StopVoice(); //StopNetworkVoice

};
