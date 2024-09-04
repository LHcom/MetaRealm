// Fill out your copyright notice in the Description page of Project Settings.


#include "MR_Controller.h"

#include "MetaRealm/MetaRealm.h"
#include "Main_HUD.h"
#include "Kismet/GameplayStatics.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "Online/CoreOnline.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/OnlineIdentityInterface.h"

void AMR_Controller::PostInitializeComponents()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostInitializeComponents();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::PostNetInit()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::PostNetInit();

	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		if (NetDriver->ServerConnection)
			AB_LOG(LogABNetwork, Log, TEXT("Server Connection: %s"), *NetDriver->ServerConnection.GetName());
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::BeginPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	Super::BeginPlay();
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AMR_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// �׼� Ű ���ε�.
	InputComponent->BindAction(TEXT("Chat"), EInputEvent::IE_Pressed, this, &AMR_Controller::FocusChatInputText);
}

void AMR_Controller::MoveToMeetingRoomMap()
{
	ClientTravel("/Game/KSK/Maps/SK_MeetingRoomMap", ETravelType::TRAVEL_Absolute);
}

void AMR_Controller::MoveToMainMap()
{
	ClientTravel("/Game/KHH/KHH_TestMap/KHH_TESTMap", ETravelType::TRAVEL_Absolute);
}

void AMR_Controller::SendMessage(const FText& Text)
{
	// �¶��� ����ý��ۿ��� Identity �������̽��� ������
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
		if (Identity.IsValid())
		{
			// 0��° ���� �÷��̾��� ���� ID�� ������
			TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(0);
			if (UserId.IsValid())
			{
				// ���� �г����� ������
				FString UserName = Identity->GetPlayerNickname(*UserId);
				FString Message = FString::Printf(TEXT("%s : %s"), *UserName, *Text.ToString());

				// ������ �޽����� ���� (CtoS_SendMessage ȣ��)
				CtoS_SendMessage(Message);
			}
		}
	}
}

void AMR_Controller::FocusGame()
{
	SetInputMode(FInputModeGameOnly());
}

void AMR_Controller::FocusChatInputText()
{
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(HUD->GetChatInputTextObject());

	SetInputMode(InputMode);
}

void AMR_Controller::CtoS_SendMessage_Implementation(const FString& Message)
{
	// ���������� ��� PlayerController���� �̺�Ʈ�� ������.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetPawn()->GetWorld(), APlayerController::StaticClass(), OutActors);
	for (AActor* OutActor : OutActors)
	{
		AMR_Controller* PC = Cast<AMR_Controller>(OutActor);
		if (PC)
		{
			PC->StoC_SendMessage(Message);
		}
	}
}

void AMR_Controller::StoC_SendMessage_Implementation(const FString& Message)
{
	// ������ Ŭ���̾�Ʈ�� �� �̺�Ʈ�� �޾Ƽ� �����Ѵ�.
	AMain_HUD* HUD = GetHUD<AMain_HUD>();
	if (HUD == nullptr) return;

	HUD->AddChatMessage(Message);
}