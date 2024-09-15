// Fill out your copyright notice in the Description page of Project Settings.


#include "BDVocieChatCharacter.h"
#include "Net/VoiceConfig.h" //VOIPTalker 헤더
#include "GameFramework/PlayerState.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/VoiceInterface.h"

// Sets default values
ABDVocieChatCharacter::ABDVocieChatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// VOIP Talker 컴포넌트를 생성하고, VOIPTalkerComponent 포인터에 할당합니다.
	VOIPTalkerComponent = CreateDefaultSubobject<UVOIPTalker>(TEXT("VOIPTalker"));

}

// Called when the game starts or when spawned
void ABDVocieChatCharacter::BeginPlay()
{
	Super::BeginPlay();

	// VOIP 초기화 작업을 호출합니다.
	InitializeVOIP();
}

// Called every frame
void ABDVocieChatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABDVocieChatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// VOIP 초기화 작업을 수행합니다.
void ABDVocieChatCharacter::InitializeVOIP()
{
	if (VOIPTalkerComponent)
	{
		// VOIPTalkerComponent가 유효한지 확인합니다.
		if (IsValid(VOIPTalkerComponent))
		{
			// 플레이어 상태에 VOIPTalker를 등록합니다.
			RegisterWithPlayerState();

			// 마이크 임계값을 설정합니다.
			SetMicThreshold(-1.0f);

			// 로컬 플레이어가 제어 중일 때만 VOIP 관련 설정을 진행합니다.
			if (IsLocallyControlled())
			{
				// 콘솔 명령을 실행하여 VOIP를 활성화합니다.
				APlayerController* PlayerController = Cast<APlayerController>(GetController());
				if (PlayerController)
				{
					PlayerController->ConsoleCommand("OSS.VoiceLoopback 1");
				}
			}

			// 원격 Talker 등록
			RegisterRemoteTalker();
		}
	}
}

void ABDVocieChatCharacter::SetUpNetworkVoice()
{
	if (IsLocallyControlled())
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		if (PlayerController)
		{
			IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
			if (OnlineSub)
			{
				IOnlineVoicePtr VoiceInterface = OnlineSub->GetVoiceInterface();
				if (VoiceInterface.IsValid())
				{
					// 플레이어에 Voice Channel 할당
					VoiceInterface->StartNetworkedVoice(PlayerController->GetLocalPlayer()->GetControllerId());
				}
			}
		}
	}
}

void ABDVocieChatCharacter::StopVoice()
{
	if (IsLocallyControlled())
	{
		APlayerController* PlayerController = GetController<APlayerController>();
		if (PlayerController)
		{
			IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
			if (OnlineSub)
			{
				IOnlineVoicePtr VoiceInterface = OnlineSub->GetVoiceInterface();
				if (VoiceInterface.IsValid())
				{
					VoiceInterface->StopNetworkedVoice(PlayerController->GetLocalPlayer()->GetControllerId());
				}
			}
		}
	}
}

// 마이크 임계값을 설정합니다.
void ABDVocieChatCharacter::SetMicThreshold(float Threshold)
{
	if (VOIPTalkerComponent)
	{
		UVOIPStatics::SetMicThreshold(Threshold);
	}
}

// 플레이어 상태에 등록합니다.
void ABDVocieChatCharacter::RegisterWithPlayerState()
{
	if (VOIPTalkerComponent && GetPlayerState())
	{
		VOIPTalkerComponent->RegisterWithPlayerState(GetPlayerState());
	}
}

// 로컬 플레이어가 제어 중인지 확인합니다.
bool ABDVocieChatCharacter::IsLocallyControlled() const
{
	return IsPlayerControlled();
}


// 원격 Talker 등록 함수
void ABDVocieChatCharacter::RegisterRemoteTalker()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub)
		{
			IOnlineVoicePtr VoiceInterface = OnlineSub->GetVoiceInterface();
			if (VoiceInterface.IsValid())
			{
				// 플레이어의 고유 네트워크 ID를 가져옵니다.
				TSharedPtr<const FUniqueNetId> UniqueNetId = PlayerController->PlayerState->GetUniqueId().GetUniqueNetId();

				if (UniqueNetId.IsValid())
				{
					// 고유 네트워크 ID를 사용하여 원격 Talker를 등록합니다.
					VoiceInterface->RegisterRemoteTalker(*UniqueNetId);
				}
			}
		}
	}
}
