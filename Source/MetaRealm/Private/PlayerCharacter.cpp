// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include <chrono>

#include "BoardStruct.h"
#include "EngineUtils.h"
#include "HttpLib.h"
#include "InteractionWidget.h"
#include "LoginActor.h"
#include "MemoWidget.h"
#include "MessagePopupWidget.h"
#include "MetaRealmGameState.h"
#include "MR_Controller.h"
#include "NetGameInstance.h"
#include "OnlineSubsystem.h"
#include "ProceedingWidget.h"
#include "WhiteBoardActor.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Materials/Material.h"
#include "ReactionUI.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "WindowList.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 플레이어에 Player Widget 붙이기=========================================================================
	PlayerUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerUI"));
	if (PlayerUI)
	{
		PlayerUI->SetupAttachment(RootComponent);
		PlayerUI->SetWidgetSpace(EWidgetSpace::Screen);
		PlayerUI->SetOnlyOwnerSee(true);
	}
	ConstructorHelpers::FClassFinder<UUserWidget> PlayerUIClass(TEXT("/Game/KHH/UI/UI/WBP_Player.WBP_Player_C"));
	if (PlayerUIClass.Succeeded())
	{
		PlayerUI->SetWidgetClass(PlayerUIClass.Class);
		PlayerUI->SetDrawSize(FVector2D(1920 , 1080));
	}

	// 플레이어 Reaction UI 관련 애들=========================================================================

	ReactionUIComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ReactionUI"));
	ReactionUIComponent->SetupAttachment(RootComponent);
	ReactionUIComponent->SetRelativeLocation(FVector(0 , 0 , 300));

	ConstructorHelpers::FClassFinder<UUserWidget> ReactionUIClass(TEXT("/Game/KSK/UI/SKWBP_Reaction.SKWBP_Reaction_C"));
	if (ReactionUIClass.Succeeded())
	{
		ReactionUIComponent->SetWidgetClass(ReactionUIClass.Class);
		ReactionUIComponent->SetDrawSize(FVector2D(200 , 200));
		UE_LOG(LogTemp , Warning , TEXT("=========================================="));
	}


	// 플레이어 상태 색 관련 애들=========================================================================

	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
	Cylinder->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(
		TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (tempMesh.Succeeded())
	{
		Cylinder->SetStaticMesh(tempMesh.Object);
		Cylinder->SetRelativeLocation(FVector(0 , 0 , -90));
		Cylinder->SetRelativeScale3D(FVector(2.0f , 2.0f , 0.035f));
	}
	/*ConstructorHelpers::FObjectFinder<UMaterial> CylinderMesh1(TEXT("/Game/KSK/Material/CylinderMaterial1"));
	if (CylinderMesh1.Succeeded())
	{
		Cylinder->SetMaterial(0 , CylinderMesh1.Object);
		CylinderMaterial1 = CylinderMesh1.Object;
	}

	ConstructorHelpers::FObjectFinder<UMaterial> CylinderMesh2(TEXT("/Game/KSK/Material/CylinderMaterial2"));
	if (CylinderMesh2.Succeeded())
	{
		CylinderMaterial2 = CylinderMesh2.Object;
	}

	ConstructorHelpers::FObjectFinder<UMaterial> CylinderMesh3(TEXT("/Game/KSK/Material/CylinderMaterial3"));
	if (CylinderMesh3.Succeeded())
	{
		CylinderMaterial3 = CylinderMesh3.Object;
	}*/
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

	ProceedingWidget = CastChecked<UProceedingWidget>(CreateWidget(GetWorld() , ProceedingFactory));
	if (ProceedingWidget)
	{
		ProceedingWidget->AddToViewport(0);
		ProceedingWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerCharacter::initMemoUI()
{
	auto pc = Cast<AMR_Controller>(Controller);
	if (nullptr == pc)
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] Player Controller is null"));
		//MemoWidget = nullptr;
		return;
	}

	if (!pc->MemoUIFactory)
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoFactory is null"));
		return;
	}

	pc->MemoUI = CastChecked<UMemoWidget>(CreateWidget(GetWorld() , pc->MemoUIFactory));
	if (pc->MemoUI)
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoWidget is not null"));
		MemoWidget = pc->MemoUI;
		MemoWidget->AddToViewport(0);
		MemoWidget->SetVisibility(ESlateVisibility::Hidden);

		if (auto gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()))
		{
			MemoWidget->eTxtBoard->SetText(FText::FromString(gs->gsContent));
		}
	}
	else
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoWidget is null"));
	}
}

void APlayerCharacter::initWindowListUI()
{
	auto pc = Cast<AMR_Controller>(Controller);
	if ( nullptr == pc )
	{
		UE_LOG(LogTemp , Warning , TEXT("[initWindowList] Player Controller is null"));
		return;
	}

	if ( !pc->MemoUIFactory )
	{
		UE_LOG(LogTemp , Warning , TEXT("[initWindowList] MemoFactory is null"));
		return;
	}

	pc->WindowListUI = CastChecked<UWindowList>(CreateWidget(GetWorld() , pc->WindowListFactory));
	if ( pc->WindowListUI )
	{
		UE_LOG(LogTemp , Warning , TEXT("[initWindowList] MemoWidget is not null"));
		WindowListWidget = pc->WindowListUI;
		WindowListWidget->AddToViewport(0);
		WindowListWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoWidget is null"));
	}
}

void APlayerCharacter::ShowWindowListUI()
{
	if ( WindowListWidget ) {
		WindowListWidget->SetVisibility(ESlateVisibility::Visible);
	}
}


void APlayerCharacter::ShowProceedingUI()
{
	if (ProceedingWidget)
	{
		ProceedingWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

FString APlayerCharacter::GetSystemTime()
{
	// 현재 시스템 시간을 가져오기
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// tm 구조체로 변환 (로컬 시간)
	std::tm localTime;
	localtime_s(&localTime , &currentTime);

	// 시간 포맷 설정 (yyyy-MM-dd HH:mm:ss)
	char buffer[100];
	std::strftime(buffer , sizeof(buffer) , "%Y-%m-%d %H:%M:%S" , &localTime);

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

	if (IsLocallyControlled())
	{
		initProceedingUI();
		initMemoUI();
		initMsgUI();
	}

	if (PlayerUI)
	{
		if (IsLocallyControlled())
		{
			PlayerUI->SetVisibility(true);
		}
		else
		{
			PlayerUI->SetVisibility(false);
		}
	}

	ReactionComp = Cast<UReactionUI>(ReactionUIComponent->GetWidget());

	FString CurrentMapName = UGameplayStatics::GetCurrentLevelName(GetWorld());

	if (CurrentMapName == "LobyMap")
	{
		TArray<AActor*> HttpActorArr;
		UGameplayStatics::GetAllActorsWithTag(GetWorld() , FName("HTTP") , HttpActorArr);
		if (HttpActorArr.Num() > 0)
		{
			HttpActor = Cast<AHttpLib>(HttpActorArr[0]);
		}
	}
	else {
		//initWindowListUI();
	}

	if (auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()))
	{
		UE_LOG(LogTemp , Warning , TEXT("Token Address : %s") , *(gi->TkAdrr.IsEmpty()?"":gi->TkAdrr));
	}
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
	UE_LOG(LogTemp , Warning , TEXT("[ServerRPC_ContentSave] Content : %s") , *strContent);
	// 서버 RPC로 들어온 변수값을
	// 멀티캐스트 RPC로 뿌려준다.
	MulticastRPC_ContentSave(strContent);

	// 게시판에 저장된 내용을 DataTable에 저장한다.
	FBoardStruct newData;
	newData.ContentString = strContent;
	auto gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance());
	if (gi)
	{
		gi->SetBoardData(newData);
		gi->SaveBoardDTToCSV();
	}
}

void APlayerCharacter::MulticastRPC_ContentSave_Implementation(const FString& strContent)
{
	// 게임스테이트에 있는 gsContent에 값을 넣는다.
	// gsContent는 Replicated 상태이기 때문에 값이 복사된다.
	auto gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState());
	if (gs)
	{
		gs->gsContent = strContent;
	}
}

void APlayerCharacter::ServerSetReaction_Implementation(int32 ReactionIdx)
{
	MulticastSetReaction(ReactionIdx);
}

void APlayerCharacter::MulticastSetReaction_Implementation(int32 ReactionIdx)
{
	ShowReaction(ReactionIdx);
}

void APlayerCharacter::ShowReaction(int32 ReactionIdx)
{
	FTimerHandle Handle;
	UTexture2D* ReactionTexture = GetReactionTextureFromId(ReactionIdx);
	if (ReactionTexture && ReactionComp && ReactionComp->Image2)
	{
		ReactionComp->Image2->SetVisibility(ESlateVisibility::Visible);
		ReactionComp->Image2->SetBrushFromTexture(ReactionTexture);
		GetWorld()->GetTimerManager().SetTimer(Handle , this , &APlayerCharacter::HideReaction , 3.0f , false);
	}
}

void APlayerCharacter::HideReaction()
{
	ReactionComp->Image2->SetVisibility(ESlateVisibility::Hidden);
}

UTexture2D* APlayerCharacter::GetReactionTextureFromId(int32 ReactionIdx)
{
	switch (ReactionIdx)
	{
	case 1: return ReactionArray[0];
	case 2: return ReactionArray[1];
	case 3: return ReactionArray[2];
	case 4: return ReactionArray[3];
	case 5: return ReactionArray[4];
	case 6: return ReactionArray[5];
	case 7: return ReactionArray[6];
	case 8: return ReactionArray[7];
	case 9: return ReactionArray[8];
	case 10: return ReactionArray[9];
	case 11: return ReactionArray[10];
	case 12: return ReactionArray[11];
	case 13: return ReactionArray[12];
	case 14: return ReactionArray[13];
	default: return nullptr;
	}
}



void APlayerCharacter::ServerSetCylinderMaterial_Implementation(int32 value)
{
	MulticastSetCylinderMaterial(value);
}

void APlayerCharacter::MulticastSetCylinderMaterial_Implementation(int32 value)
{	
	SetCylinderMaterial(value);	
}

void APlayerCharacter::SetCylinderMaterial(int32 value)
{
	if ( value == 1 && CylinderMaterial1 )
	{
		Cylinder->SetMaterial(0 , CylinderMaterial1);
	}
	else if ( value == 2 && CylinderMaterial2 )
	{
		Cylinder->SetMaterial(0 , CylinderMaterial2);
	}
	else if ( value == 3 && CylinderMaterial3 )
	{
		Cylinder->SetMaterial(0 , CylinderMaterial3);
	}
}

void APlayerCharacter::SignUp(const FString& JSON)
{
	if (!HttpActor)
	{
		UE_LOG(LogTemp , Warning , TEXT("HttpActor Is Null"));
		return;
	}

	HttpActor->ReqSignUp(JSON);
}

void APlayerCharacter::getResSignUp(FString& ret)
{
	if (ret.Equals("Successes to register user"))
	{
		// 성공
		// 회원가입 UI를 닫고
		if (ALoginActor* loginActor = Cast<ALoginActor>(
			UGameplayStatics::GetActorOfClass(GetWorld() , ALoginActor::StaticClass())))
		{
			loginActor->HideSignUpUI();
		}
		// 회원가입 성공 메세지박스를 출력한다.
		FString successMSG = FString::Printf(TEXT("회원가입을 성공하였습니다!!!"));
		MsgWidget->txtMessage->SetText(FText::FromString(successMSG));
		MsgWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		// 실패
		if (ALoginActor* loginActor = Cast<ALoginActor>(
			UGameplayStatics::GetActorOfClass(GetWorld() , ALoginActor::StaticClass())))
		{
			loginActor->ShowErrMsg(true , ret);
		}
	}
}

void APlayerCharacter::Login(const FString& JSON)
{
	if (!HttpActor)
	{
		UE_LOG(LogTemp , Warning , TEXT("HttpActor Is Null"));
		return;
	}

	HttpActor->ReqLogin(JSON);
}

void APlayerCharacter::getResLogin(FString& ret)
{
	if (ret != "Successes to login")
	{
		if (ALoginActor* loginActor = Cast<ALoginActor>(
			UGameplayStatics::GetActorOfClass(GetWorld() , ALoginActor::StaticClass())))
		{
			loginActor->ShowErrMsg(false , ret);
		}
	}
	else
	{
		if (ALoginActor* loginActor = Cast<ALoginActor>(
			UGameplayStatics::GetActorOfClass(GetWorld() , ALoginActor::StaticClass())))
		{
			loginActor->ShowErrMsg(false , ret);
		}

		auto GI = GetWorld()->GetGameInstance<UNetGameInstance>();
		if (GI)
		{
			GI->LogInSession();
		}
	}
}

void APlayerCharacter::initMsgUI()
{
	auto pc = Cast<AMR_Controller>(Controller);
	if (nullptr == pc)
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] Player Controller is null"));
		return;
	}

	if (!pc->MsgUIFactory)
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoFactory is null"));
		return;
	}

	pc->MsgUI = CastChecked<UMessagePopupWidget>(CreateWidget(GetWorld() , pc->MsgUIFactory));
	if (pc->MsgUI)
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoWidget is not null"));
		MsgWidget = pc->MsgUI;
		MsgWidget->AddToViewport(99);
		MsgWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp , Warning , TEXT("[initMemoUI] MemoWidget is null"));
	}
}

void APlayerCharacter::ServerRPC_SetStreamingPlayer_Implementation(const FString& PlayerID, const bool bAddPlayer)
{
	if (auto gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()))
	{
		if (bAddPlayer)
		{
			if (gs->ArrStreamingUserID.Find(PlayerID) >= 0)
				return;

			gs->ArrStreamingUserID.Add(PlayerID);
			if(HasAuthority())
				gs->OnRep_StreamingID();
		}
		else
		{
			if (gs->ArrStreamingUserID.Num() == 0)
				return;

			if (gs->ArrStreamingUserID.Find(PlayerID) < 0)
				return;

			gs->ArrStreamingUserID.Remove(PlayerID);
			if(HasAuthority())
				gs->OnRep_StreamingID();
		}
	}
}

void APlayerCharacter::Multicast_SetStreamingPlayer_Implementation()
{
	
}
