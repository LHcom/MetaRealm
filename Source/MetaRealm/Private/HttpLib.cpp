// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpLib.h"

#include "HttpModule.h"
#include "JsonParseLib.h"
#include "MetaRealmGameState.h"
#include "MetaRealmGM.h"
#include "NetGameInstance.h"
#include "PlayerCharacter.h"
#include "ProceedStruct.h"
#include "Kismet/GameplayStatics.h"
#include "MetaRealm/MetaRealm.h"

void AHttpLib::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	gm = Cast<AMetaRealmGM>(GetWorld()->GetAuthGameMode());
	if (gm)
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("gm is not null"));
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("gm is null"));
	}
}

void AHttpLib::ReqSignUp(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetVerb("POST");
	req->SetURL(SignUpURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &AHttpLib::OnResSignUp);
	req->ProcessRequest();
}

void AHttpLib::OnResSignUp(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		UE_LOG(LogTemp, Warning, TEXT("Request Success"));
		FString Result = Response->GetContentAsString();
		//UJsonParseLib::SignUpJsonParse(Result);
		UE_LOG(LogTemp, Warning, TEXT("Request Result : %s"), *Result);

		if (player)
			player->getResSignUp(Result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
		if (player)
			player->getResSignUp("Request POST Failed");
	}
}

void AHttpLib::ReqLogin(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetVerb("POST");
	req->SetURL(LoginURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &AHttpLib::OnResLogin);
	req->ProcessRequest();
}

void AHttpLib::OnResLogin(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		UE_LOG(LogTemp, Warning, TEXT("Request Success"));
		FString Result = Response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("Request Result : %s"), *Result);
		FUserInfo userInfo = UJsonParseLib::LoginJsonParse(Result);
		if (userInfo.MSG == "로그인 성공")
		{
			FString Authorization = Response->GetHeader("Authorization");
			userInfo.TkAddr = Authorization;
			UE_LOG(LogTemp, Warning, TEXT("Authorization : %s"), *Authorization);
		}

		if (player)
			player->getResLogin(userInfo.MSG);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
		if (player)
			player->getResLogin("Request POST Failed");
	}
}

void AHttpLib::ReqSoundToText(const FString& FilePath)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SoundToTextURL);
	req->SetVerb("POST");
	FString Boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
	req->SetHeader(TEXT("Content-Type"), TEXT("multipart/form-data; boundary=") + Boundary);

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read file: %s"), *FilePath);
		return;
	}

	// multipart/form-data 포맷에 맞게 데이터 구성
	FString BeginBoundary = FString("--") + Boundary + "\r\n";
	FString EndBoundary = FString("--") + Boundary + "--\r\n";

	// 파일 부분 구성
	FString FileHeader = "Content-Disposition: form-data; name=\"voice\"; filename=\"" +
		FPaths::GetCleanFilename(FilePath) + "\"\r\n";
	FileHeader.Append("Content-Type: audio/wav\r\n\r\n");

	// 전체 페이로드 구성
	FString PayloadString = BeginBoundary + FileHeader;
	TArray<uint8> Payload;
	Payload.Append((uint8*)TCHAR_TO_UTF8(*PayloadString), PayloadString.Len());
	Payload.Append(FileData);
	FString EndPayloadString = "\r\n" + EndBoundary;
	Payload.Append((uint8*)TCHAR_TO_UTF8(*EndPayloadString), EndPayloadString.Len());

	// 요청 바디 설정
	req->SetContent(Payload);

	req->OnProcessRequestComplete().BindUObject(this, &AHttpLib::OnResSoundToText);
	req->ProcessRequest();


	/*req->SetHeader(TEXT("Content-Type"), TEXT("audio/wav"));
	req->OnProcessRequestComplete().BindUObject(this, &AHttpLib::OnResSoundToText);
	TArray<uint8> FileContent;
	if (FFileHelper::LoadFileToArray(FileContent, *FilePath)) {
		req->SetContent(FileContent);
		req->ProcessRequest();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
	}*/
}

void AHttpLib::OnResSoundToText(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		UE_LOG(LogTemp, Warning, TEXT("Request Success"));
		FString Result = Response->GetContentAsString();
		FString outStrMessage;
		UJsonParseLib::SoundToTextJsonParse(Result, outStrMessage);
		if (player)
		{
			FString strMeetingTime = FString::Printf(TEXT("%s%s%s"), *player->MeetingStartTime, TEXT("~"),
			                                         *player->MeetingEndTime);
			FString meetingMember = "";
			if (gm)
			{
				meetingMember = gm->MeetingMember;
				gm->MeetingMember = "";
			}

			// 회의록을 구조체에 저장
			FProceedStruct recordInfo;
			recordInfo.StrMemberList = meetingMember;
			recordInfo.StrMeetingTime = strMeetingTime;
			recordInfo.StrContent = outStrMessage.IsEmpty() ? "" : outStrMessage;
			// 게임스테이트에 존재하는 구조체 배열에 추가 
			if (auto* gs = Cast<AMetaRealmGameState>(GetWorld()->GetGameState()))
			{
				gs->ArrRecordInfo.Add(recordInfo);
				
				// 호스트일 경우에는 한번 호출해줘야함.
				if (HasAuthority())
					gs->OnRep_Proceeding();
			}
			if(auto* gi = Cast<UNetGameInstance>(GetWorld()->GetGameInstance()))
			{
				gi->SetProceedData(recordInfo);
				gi->SaveProceedDTToCSV();
			}
			//player->setTextProceedingUI(meetingMember, strMeetingTime, outStrMessage);
		}
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
	}
}

void AHttpLib::ReqGenerateColor(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SignUpURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &AHttpLib::OnResGenerateColor);
	req->ProcessRequest();
}

void AHttpLib::OnResGenerateColor(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		UE_LOG(LogTemp, Warning, TEXT("Request Success"));
		FString Result = Response->GetContentAsString();
		UJsonParseLib::GenerateColorJsonParse(Result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
	}
}
