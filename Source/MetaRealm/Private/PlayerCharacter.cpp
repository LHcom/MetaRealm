// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Reaction_UserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../../../Plugins/Runtime/AudioCapture/Source/AudioCapture/Public/AudioCaptureComponent.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->SetRelativeScale3D(FVector(0.85f));
	}
	// 이동방향으로 회전하도록 처리하고싶다.
	GetCharacterMovement()->bOrientRotationToMovement = true;

	ReactionComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ReactionComp"));
	ReactionComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<UReaction_UserWidget> TempReactionUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/KHH_Reaction_UserWidget.KHH_Reaction_UserWidget_C'"));

	if (TempReactionUI.Succeeded())
	{
		ReactionComp->SetWidgetClass(TempReactionUI.Class);
		ReactionComp->SetDrawSize(FVector2D(100, 100));
		ReactionComp->SetRelativeLocation(FVector(0, 0, 120));
	}

	AudioCapture = CreateDefaultSubobject<UAudioCaptureComponent>(TEXT("AudioCapture"));
	AudioCapture->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

