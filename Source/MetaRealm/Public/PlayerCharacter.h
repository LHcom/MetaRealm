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
};
