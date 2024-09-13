// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteBoardActor.h"

#include "MemoWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
AWhiteBoardActor::AWhiteBoardActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootScene = CreateDefaultSubobject<USceneComponent>(TEXT("rootScene"));
	RootComponent = rootScene;
	
	ConstructorHelpers::FClassFinder<UMemoWidget> tmpMemo(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/UI/WBP_Memo.WBP_Memo_C'"));
	WhiteBoardWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WhiteBoardWidget"));
	WhiteBoardWidget->AttachToComponent(rootScene, FAttachmentTransformRules::KeepRelativeTransform);
	if (tmpMemo.Succeeded())
	{
		WhiteBoardWidget->SetWidgetClass(tmpMemo.Class);
	}
}

// Called when the game starts or when spawned
void AWhiteBoardActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWhiteBoardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
