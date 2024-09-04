// Fill out your copyright notice in the Description page of Project Settings.


#include "BDVocieChatCharacter.h"
#include "Net/VoiceConfig.h" //VOIPTalker ���
#include "GameFramework/PlayerState.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/OnlineSubsystem.h"
#include "../../../../Plugins/Online/OnlineSubsystem/Source/Public/Interfaces/VoiceInterface.h"

// Sets default values
ABDVocieChatCharacter::ABDVocieChatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// VOIP Talker ������Ʈ�� �����ϰ�, VOIPTalkerComponent �����Ϳ� �Ҵ��մϴ�.
	VOIPTalkerComponent = CreateDefaultSubobject<UVOIPTalker>(TEXT("VOIPTalker"));

}

// Called when the game starts or when spawned
void ABDVocieChatCharacter::BeginPlay()
{
	Super::BeginPlay();

	// VOIP �ʱ�ȭ �۾��� ȣ���մϴ�.
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

// VOIP �ʱ�ȭ �۾��� �����մϴ�.
void ABDVocieChatCharacter::InitializeVOIP()
{
	if (VOIPTalkerComponent)
	{
		// VOIPTalkerComponent�� ��ȿ���� Ȯ���մϴ�.
		if (IsValid(VOIPTalkerComponent))
		{
			// �÷��̾� ���¿� VOIPTalker�� ����մϴ�.
			RegisterWithPlayerState();

			// ����ũ �Ӱ谪�� �����մϴ�.
			SetMicThreshold(-1.0f);

			// ���� �÷��̾ ���� ���� ���� VOIP ���� ������ �����մϴ�.
			if (IsLocallyControlled())
			{
				// �ܼ� ����� �����Ͽ� VOIP�� Ȱ��ȭ�մϴ�.
				APlayerController* PlayerController = Cast<APlayerController>(GetController());
				if (PlayerController)
				{
					PlayerController->ConsoleCommand("OSS.VoiceLoopback 1");
				}
			}

			// ���� Talker ���
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
					// �÷��̾ Voice Channel �Ҵ�
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

// ����ũ �Ӱ谪�� �����մϴ�.
void ABDVocieChatCharacter::SetMicThreshold(float Threshold)
{
	if (VOIPTalkerComponent)
	{
		UVOIPStatics::SetMicThreshold(Threshold);
	}
}

// �÷��̾� ���¿� ����մϴ�.
void ABDVocieChatCharacter::RegisterWithPlayerState()
{
	if (VOIPTalkerComponent && GetPlayerState())
	{
		VOIPTalkerComponent->RegisterWithPlayerState(GetPlayerState());
	}
}

// ���� �÷��̾ ���� ������ Ȯ���մϴ�.
bool ABDVocieChatCharacter::IsLocallyControlled() const
{
	return IsPlayerControlled();
}


// ���� Talker ��� �Լ�
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
				// �÷��̾��� ���� ��Ʈ��ũ ID�� �����ɴϴ�.
				TSharedPtr<const FUniqueNetId> UniqueNetId = PlayerController->PlayerState->UniqueId.GetUniqueNetId();

				if (UniqueNetId.IsValid())
				{
					// ���� ��Ʈ��ũ ID�� ����Ͽ� ���� Talker�� ����մϴ�.
					VoiceInterface->RegisterRemoteTalker(*UniqueNetId);
				}
			}
		}
	}
}
