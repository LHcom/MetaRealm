// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpLib.h"

#include "HttpModule.h"
#include "JsonParseLib.h"
#include "MetaRealmGM.h"
#include "PlayerCharacter.h"
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
		UJsonParseLib::SignUpJsonParse(Result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
	}
}

void AHttpLib::ReqLogin(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SignUpURL);
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
		UJsonParseLib::LoginJsonParse(Result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
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
			FString meetingMember="";
			if(gm)
			{
				meetingMember=gm->MeetingMember;
				gm->MeetingMember="";				
			}
				
			player->setTextProceedingUI(meetingMember, strMeetingTime, outStrMessage);
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
