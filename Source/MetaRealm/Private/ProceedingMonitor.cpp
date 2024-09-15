// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceedingMonitor.h"

#include "PlayerCharacter.h"

// Sets default values
AProceedingMonitor::AProceedingMonitor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProceedingMonitor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProceedingMonitor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceedingMonitor::ShowProceedingUI()
{
	if(APlayerCharacter* Currplayer = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		Currplayer->ShowProceedingUI();
	}
}

