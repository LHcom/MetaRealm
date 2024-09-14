// Fill out your copyright notice in the Description page of Project Settings.


#include "NetGameInstance.h"
#include <string>

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "GameFramework/PlayerState.h"
#include "Online/OnlineSessionNames.h"

void UNetGameInstance::Init()
{
	Super::Init();

	// 온라인 서브 시스템 가져오자
	IOnlineSubsystem* subsys = IOnlineSubsystem::Get();
	if (subsys)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.f,
			FColor::Blue,
			FString::Printf(TEXT("Found Subsystem %s"), *subsys->GetSubsystemName().ToString())
		);

		// 세션 인터페이스 가져오자
		sessionInterface = subsys->GetSessionInterface();
		sessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UNetGameInstance::OnCreateSessionComplete);
		sessionInterface->OnDestroySessionCompleteDelegates.AddUObject(
			this, &UNetGameInstance::OnDestroySessionComplete);
		sessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UNetGameInstance::OnFindSessionComplete);
		sessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UNetGameInstance::OnJoinSessionComplete);
	}
}

void UNetGameInstance::CreateMySession(FString roomName)
{
	if (sessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("sessionInterface isValid"));
		auto ExistingSession = sessionInterface->GetNamedSession(FName(mySessionName)); // 현재 세션 정보 얻기
		if (ExistingSession) // 세션이 이미 존재한다면
		{
			UE_LOG(LogTemp, Warning, TEXT("Existing session found. Destroying the session..."));
			//sessionInterface->DestroySession(FName(mySessionName)); // 기존에 명명된 세션을 파괴
			DestroyMySession(true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("session is not found."));
			FOnlineSessionSettings sessionSettings;
			if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
			// OnlineSubsystem 이 NULL 로 세팅되면 (NULL : 로컬 연결 설정)
			{
				sessionSettings.bIsLANMatch = true; // true 시 : 같은 네트워크에 있는 사람을 찾음 (로컬 연결 설정) 
			}

			else
			{
				sessionSettings.bIsLANMatch = false; // false 시 : 다른 네트워크와 연결 가능하도록 함. (Steam, XBox 등 공식플랫폼 연결 설정)
			}

			// true 세션이 검색 된다.
			sessionSettings.bShouldAdvertise = true;

			// steam 사용하면 해당 옵션이 true 세션을 만들 수 있다.
			sessionSettings.bUseLobbiesIfAvailable = true;

			// 내가 게임중인 아닌지를 보여줄건지
			sessionSettings.bUsesPresence = true;
			// 게임 플레이 중에 참여할 수 있게
			sessionSettings.bAllowJoinInProgress = true;
			sessionSettings.bAllowJoinViaPresence = true;

			// 인원 수 
			sessionSettings.NumPublicConnections = 10;

			// base64로 Encode
			//roomName = StringBase64Encode(roomName);
			sessionSettings.Set(FName("ROOM_NAME"), roomName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);


			// 세션 생성 요청
			FUniqueNetIdPtr netID = GetWorld()->GetFirstLocalPlayerFromController()->GetUniqueNetIdForPlatformUser().
			                                    GetUniqueNetId();

			// int32 rand = FMath::RandRange(1, 100000);
			// mySessionName += FString::Printf(TEXT("%d"), rand);
			//NowSession = mySessionName;

			sessionInterface->CreateSession(0, FName(mySessionName), sessionSettings);
		}
	}
}

void UNetGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete Success -- %s"), *SessionName.ToString());
		// Battle Map 으로 이동하자
		GetWorld()->ServerTravel(TEXT("/Game/KHH/KHH_TestMap/KHH_level?listen"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete Fail"));
	}
}

void UNetGameInstance::DestroyMySession(bool bMakeSession)
{
	MakeSessionFlag = bMakeSession;

	if (sessionInterface.IsValid())
	{
		sessionInterface->DestroySession(FName(mySessionName));
	}
	// 세션 관련 데이터 초기화
	sessionSearch.Reset();
}

void UNetGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionComplete Success -- %s"), *SessionName.ToString());
		if (MakeSessionFlag)
			CreateMySession(MyroomName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnDestroySessionComplete Fail"));
	}
}

void UNetGameInstance::FindOtherSession()
{
	UE_LOG(LogTemp, Warning, TEXT("FindOtherSession Start"));
	sessionSearch = MakeShared<FOnlineSessionSearch>();

	sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	sessionSearch->MaxSearchResults = 10;

	// 세션 검색 요청
	sessionInterface->FindSessions(0, sessionSearch.ToSharedRef());
	UE_LOG(LogTemp, Warning, TEXT("FindOtherSession End"));
}

void UNetGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (sessionSearch)
		{
			auto results = sessionSearch->SearchResults;
			UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete Success - count : %d"), results.Num());

			// Create Session
			if (results.Num() == 0)
			{
				CreateMySession(MyroomName);
			}
			else
			{
				bool flag = false;
				for (int i = 0; i < results.Num(); i++)
				{
					FOnlineSessionSearchResult si = results[i];
					FString strRoomName;
					si.Session.SessionSettings.Get(FName("ROOM_NAME"), strRoomName);
					UE_LOG(LogTemp, Warning, TEXT("%s"), *si.Session.GetSessionIdStr());

					if (strRoomName != MyroomName)
						continue;

					flag = true;
					JoinOtherSession(i);
					break;
				}

				if (!flag)
					CreateMySession(MyroomName);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete Fail"));
	}
}

void UNetGameInstance::JoinOtherSession(int32 idx)
{
	auto results = sessionSearch->SearchResults;
	if (sessionInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("sessionInterface is null"));
	}
	if (results.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("results Zero"));
	}
	UE_LOG(LogTemp, Warning, TEXT("results count : %d, idx : %d"), results.Num(), idx);
	sessionInterface->JoinSession(0, FName(mySessionName), results[idx]);
}

void UNetGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type result)
{
	if (result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete Success : %s"), *SessionName.ToString());
		FString url;
		// 참여해야 하는 Listen 서버 URL을 받아 오자
		sessionInterface->GetResolvedConnectString(SessionName, url);
		UE_LOG(LogTemp, Warning, TEXT("Join session URL : %s"), *url);

		if (!url.IsEmpty())
		{
			// 해당 URL 로 접속하자
			APlayerController* pc = GetWorld()->GetFirstPlayerController();
			pc->ClientTravel(url, ETravelType::TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete Fail : %d"), result);
	}
}

void UNetGameInstance::KickPlayer(APlayerController* PlayerToKick)
{
	if (PlayerToKick && PlayerToKick->IsLocalController())
		// 플레이어를 메인 메뉴로 이동시킴
		PlayerToKick->ClientTravel("/Game/LHJ/BluePrints/Loby/LobyMap", ETravelType::TRAVEL_Absolute);
}

FString UNetGameInstance::StringBase64Encode(FString str)
{
	// Set 할 때 : FString -> UTF8 (std::string) -> TArray<uint8> -> base64 로 Encode
	std::string utf8String = TCHAR_TO_UTF8(*str);
	TArray<uint8> arrayData = TArray<uint8>((uint8*)(utf8String.c_str()), utf8String.length());
	return FBase64::Encode(arrayData);
}

FString UNetGameInstance::StringBase64Decode(FString str)
{
	// Get 할 때 : base64 로 Decode -> TArray<uint8> -> TCHAR
	TArray<uint8> arrayData;
	FBase64::Decode(str, arrayData);
	std::string ut8String((char*)(arrayData.GetData()), arrayData.Num());
	return UTF8_TO_TCHAR(ut8String.c_str());
}

void UNetGameInstance::LogInSession()
{
	UE_LOG(LogTemp, Warning, TEXT("LogInSession Start"));
	FindOtherSession();
	UE_LOG(LogTemp, Warning, TEXT("LogInSession End"));
}
