// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpLib.h"

#include "HttpModule.h"
#include "JsonParseLib.h"

void UHttpLib::ReqSignUp(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SignUpURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &UHttpLib::OnResSignUp);
	req->ProcessRequest();
}

void UHttpLib::OnResSignUp(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
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

void UHttpLib::ReqLogin(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SignUpURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &UHttpLib::OnResLogin);
	req->ProcessRequest();
}

void UHttpLib::OnResLogin(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
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

void UHttpLib::ReqSoundToText(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SignUpURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &UHttpLib::OnResSoundToText);
	req->ProcessRequest();
}

void UHttpLib::OnResSoundToText(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// 성공
		UE_LOG(LogTemp, Warning, TEXT("Request Success"));
		FString Result = Response->GetContentAsString();
		UJsonParseLib::SoundToTextJsonParse(Result);
	}
	else
	{
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("Request POST Failed"));
	}
}

void UHttpLib::ReqGenerateColor(const FString& JSON)
{
	FHttpModule& HttpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = HttpModule.CreateRequest();
	req->SetURL(SignUpURL);
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	req->SetContentAsString(JSON);
	req->OnProcessRequestComplete().BindUObject(this, &UHttpLib::OnResGenerateColor);
	req->ProcessRequest();
}

void UHttpLib::OnResGenerateColor(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
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
