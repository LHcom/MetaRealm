// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include <chrono>

#include "EngineUtils.h"
#include "InteractionWidget.h"
#include "MemoWidget.h"
#include "OnlineSubsystem.h"
#include "ProceedingWidget.h"
#include "WhiteBoardActor.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/OnlineIdentityInterface.h"

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

void APlayerCharacter::initProceedingUI()
{
	auto* pc = Cast<APlayerController>(Controller);
	if (nullptr == pc)
	{
		ProceedingWidget = nullptr;
		return;
	}

	if (!ProceedingFactory)
		return;

	ProceedingWidget = CastChecked<UProceedingWidget>(CreateWidget(GetWorld(), ProceedingFactory));
	if (ProceedingWidget)
	{
		ProceedingWidget->AddToViewport(0);
		ProceedingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacter::initMemoUI()
{
	if(!IsLocallyControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("[initMemoUI] Player Controller is not Local"));
		return;
	}

	auto* pc = Cast<APlayerController>(Controller);
	if (nullptr == pc)
	{
		UE_LOG(LogTemp, Warning, TEXT("[initMemoUI] Player Controller is null"));
		MemoWidget = nullptr;
		return;
	}

	if (!MemoFactory)
	{
		UE_LOG(LogTemp, Warning, TEXT("[initMemoUI] MemoFactory is null"));
		return;
	}

	MemoWidget = CastChecked<UMemoWidget>(CreateWidget(GetWorld(), MemoFactory));
	if (MemoWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("[initMemoUI] MemoWidget is not null"));
		MemoWidget->AddToViewport(0);
		MemoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[initMemoUI] MemoWidget is null"));
	}
}

void APlayerCharacter::setTextProceedingUI(FString& strMember, FString& strTime, FString& strCondensation)
{
	if (ProceedingWidget)
	{
		ProceedingWidget->SetVisibility(ESlateVisibility::Visible);

		if (!strMember.IsEmpty())
			ProceedingWidget->txt_Member->SetText(FText::FromString(strMember));
		if (!strTime.IsEmpty())
			ProceedingWidget->txt_Time->SetText(FText::FromString(strTime));
		if (!strCondensation.IsEmpty())
			ProceedingWidget->txt_Condensation->SetText(FText::FromString(strCondensation));

		strMember = "";
		strTime = "";
		strCondensation = "";
	}
}

FString APlayerCharacter::GetSystemTime()
{
	// 현재 시스템 시간을 가져오기
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// tm 구조체로 변환 (로컬 시간)
	std::tm localTime;
	localtime_s(&localTime, &currentTime);

	// 시간 포맷 설정 (yyyy-MM-dd HH:mm:ss)
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);

	// FString로 변환하여 Unreal에서 출력
	FString TimeString = FString(buffer);

	return TimeString;
}

FString APlayerCharacter::GetMemberName()
{
	FString UserName;
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
		if (Identity.IsValid())
		{
			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);
			if (UserId.IsValid())
			{
				UserName = Identity->GetPlayerNickname(*UserId);
			}
		}
	}

	return UserName;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	initProceedingUI();
	initMemoUI();
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

void APlayerCharacter::ServerRPC_ContentSave_Implementation(const FString& strContent)
{
	UE_LOG(LogTemp, Warning, TEXT("Content : %s"), *strContent);
	MulticastRPC_ContentSave(strContent);
}

void APlayerCharacter::MulticastRPC_ContentSave_Implementation(const FString& strContent)
{
	// if (!WhiteBoard)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("WhiteBoard is nullptr"));
	//
	// 	for (TActorIterator<AActor> It(GetWorld(), AActor::StaticClass()); It; ++It)
	// 	{
	// 		AActor* Actor = *It;
	// 		if (IsValid(Actor) && Actor->ActorHasTag(FName("WhiteBoard")))
	// 		{
	// 			WhiteBoard = Actor;
	// 			break;
	// 		}
	// 	}
	// }
	//
	// if (!WhiteBoard)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("realreal WhiteBoard is nullptr"));
	// 	return;
	// }
	//
	// auto boardActor = Cast<AWhiteBoardActor>(WhiteBoard);
	// if (!boardActor)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("boardActor is nullptr"));
	// 	return;
	// }
	//
	// auto board = boardActor->GetDefaultSubobjectByName(TEXT("WhiteBoardWidget"));
	// if (!board)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("board is nullptr"));
	// 	return;
	// }
	//
	// auto boardWidget = Cast<UWidgetComponent>(board);
	// if (!boardWidget)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("boardWidget is nullptr"));
	// 	return;
	// }
	//
	// auto memoComp = Cast<UMemoWidget>(boardWidget->GetUserWidgetObject());

	// if (memoComp)
	// {
	// 	//memoComp->strMemo = strContent;
	// 	memoComp->EditableText_0->SetText(FText::FromString(strContent));
	// 	UE_LOG(LogTemp, Warning, TEXT("Multicast RPC Memo Content: %s"),
	// 	       *memoComp->EditableText_0->GetText().ToString());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("memoComp is nullptr"));
	// }

	// if(IsLocallyControlled())
	// {
	// 	if (MemoWidget)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("MemoWidget is not null"));
	// 		//memoComp->strMemo = strContent;
	// 		MemoWidget->EditableText_0->SetText(FText::FromString(strContent));
	// 		UE_LOG(LogTemp, Warning, TEXT("Multicast RPC Memo Content: %s"),
	// 			   *MemoWidget->EditableText_0->GetText().ToString());
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("MemoWidget is nullptr"));
	// 	}
	// }
	//
}

void APlayerCharacter::ClientRPC_ContentSave_Implementation(const FString& strContent)
{
	if(IsLocallyControlled())
	{
		if (MemoWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("MemoWidget is not null"));
			//memoComp->strMemo = strContent;
			MemoWidget->EditableText_0->SetText(FText::FromString(strContent));
			UE_LOG(LogTemp, Warning, TEXT("Multicast RPC Memo Content: %s"),
				   *MemoWidget->EditableText_0->GetText().ToString());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MemoWidget is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("is not local player"));
	}
}