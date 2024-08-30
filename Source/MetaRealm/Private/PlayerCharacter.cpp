// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));

	//if (TempMesh.Succeeded())
	//{
	//	GetMesh()->SetSkeletalMesh(TempMesh.Object);
	//	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	//	GetMesh()->SetRelativeScale3D(FVector(0.85f));
	//}
	//// 이동방향으로 회전하도록 처리하고싶다.
	//GetCharacterMovement()->bOrientRotationToMovement = true;

	//HPComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPComp"));
	//HPComp->SetupAttachment(RootComponent);

	//ConstructorHelpers::FClassFinder<UEnemyHPWidget> TempHPUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/TPS/UI/WBP_EnemyHp.WBP_EnemyHp_C'"));

	//if (TempHPUI.Succeeded())
	//{
	//	HPComp->SetWidgetClass(TempHPUI.Class);
	//	HPComp->SetDrawSize(FVector2D(100, 20));
	//	HPComp->SetRelativeLocation(FVector(0, 0, 120));
	//}
	//FSMComp = CreateDefaultSubobject<UFSMComponent>(TEXT("FSMComp"));
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

