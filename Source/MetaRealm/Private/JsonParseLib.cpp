// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLib.h"

#include "MetaRealmGameState.h"
#include "MR_Controller.h"

FString UJsonParseLib::MakeJson(const TMap<FString , FString>& source)
{
	// source를 JsonObject 형식으로 만든다.
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	for (TPair<FString , FString> pair : source)
	{
		JsonObject->SetStringField(pair.Key , pair.Value);
	}
	// writer를 만들어서 JsonObject를 인코딩해서
	FString json;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&json);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef() , Writer);
	// 반환
	return json;
}

FString UJsonParseLib::SignUpJsonParse(const FString& strJson)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(strJson);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FString returnValue = "SignUp Failed";
	if (FJsonSerializer::Deserialize(reader , result))
	{
		if (result->HasField(TEXT("message")))
			returnValue = result->GetStringField(TEXT("message"));
		else if (result->HasField(TEXT("detailErrorDescription")))
			returnValue = result->GetStringField(TEXT("detailErrorDescription"));
	}

	// 반환을 한다.
	return returnValue;
}

FUserInfo UJsonParseLib::LoginJsonParse(const FString& strJson)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(strJson);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FUserInfo info;
	if (FJsonSerializer::Deserialize(reader , result))
	{
		if (result->HasField(TEXT("message")))
			info.MSG = result->GetStringField(TEXT("message"));
		// else if (result->HasField(TEXT("failType")))
		// 	info.MSG = result->GetStringField(TEXT("failType"));

		if (result->HasField(TEXT("token")))
			info.TkAddr = result->GetStringField(TEXT("token"));
		if (result->HasField(TEXT("userName")))
			info.NickName = result->GetStringField(TEXT("userName"));
	}
	// 반환을 한다.
	return info;
}

FString UJsonParseLib::SoundToTextJsonParse(const FString& strJson , FString& outStrMessage)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(strJson);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader , result))
	{
		//<><><> API Return 값에 따라 파싱하는게 달라져야함.
		if (result->HasField(TEXT("response")))
		{
			outStrMessage = result->GetStringField(TEXT("response"));
		}
		// TArray<TSharedPtr<FJsonValue>> parseDataList = result->GetArrayField(TEXT("items"));
		// for (auto data : parseDataList)
		// {
		// 	FString bk_nm = data->AsObject()->GetStringField("bk_nm");
		// 	FString aut_nm = data->AsObject()->GetStringField("aut_nm");
		// 	returnValue.Append(FString::Printf(TEXT("BookName : %s / AuthorName : %s\n"), *bk_nm, *aut_nm));
		// }
	}
	// 반환을 한다.
	return returnValue;
}

FString UJsonParseLib::GenerateColorJsonParse(const FString& strJson)
{
	// 리더기를 만들고
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(strJson);
	// 파싱 결과를 담을 변수 선언
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());
	// 해석을 한다.
	FString returnValue;
	if (FJsonSerializer::Deserialize(reader , result))
	{
		//<><><> API Return 값에 따라 파싱하는게 달라져야함.

		// TArray<TSharedPtr<FJsonValue>> parseDataList = result->GetArrayField(TEXT("items"));
		// for (auto data : parseDataList)
		// {
		// 	FString bk_nm = data->AsObject()->GetStringField("bk_nm");
		// 	FString aut_nm = data->AsObject()->GetStringField("aut_nm");
		// 	returnValue.Append(FString::Printf(TEXT("BookName : %s / AuthorName : %s\n"), *bk_nm, *aut_nm));
		// }
	}
	// 반환을 한다.
	return returnValue;
}
