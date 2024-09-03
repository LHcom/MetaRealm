// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginActor.h"
#include "LoginUI.h"
#include "SignUpUI.h"
#include "LobyWidget.h"

// Sets default values
ALoginActor::ALoginActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoginActor::BeginPlay()
{
	Super::BeginPlay();
	
	LoginUI = Cast<ULoginUI>(CreateWidget(GetWorld(), LoginUIFactory));
	if (LoginUI) {
		LoginUI->AddToViewport();
	}
	SignUpUI = Cast<USignUpUI>(CreateWidget(GetWorld(), SignUpUIFactory));
	if (SignUpUI) {
		SignUpUI->AddToViewport();
		SignUpUI->SetVisibility(ESlateVisibility::Hidden);
		if (LoginUI) {
			LoginUI->SignUpUI = SignUpUI;
		}
	}
	LobbyUI = Cast<ULobyWidget>(CreateWidget(GetWorld(), LobbyUIFactory));
	if (LobbyUI) {
		LobbyUI->AddToViewport();
		LobbyUI->SetVisibility(ESlateVisibility::Hidden);
		if (LoginUI) {
			LoginUI->LobbyUI = LobbyUI;
		}
	}

}

// Called every frame
void ALoginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

