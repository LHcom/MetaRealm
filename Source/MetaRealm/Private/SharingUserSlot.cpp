// Fill out your copyright notice in the Description page of Project Settings.


#include "SharingUserSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void USharingUserSlot::NativeConstruct()
{
    Super::NativeConstruct();
    // 버튼 클릭 시 호출할 함수 바인딩
    if ( UserIDButton )
    {
        UserIDButton->OnClicked.AddDynamic(this , &USharingUserSlot::OnUserIDButtonClicked);
    }
}

void USharingUserSlot::SetUserID(FString ID)
{
    // UserID를 설정하고 UI를 업데이트
    CurrentUserID = ID;

    if ( UserIDText )
    {
        UserIDText->SetText(FText::FromString(CurrentUserID));
    }

    // 추가로 필요한 동작을 이곳에서 수행할 수 있음 (예: 특정 사용자에 대한 화면 공유 시작 등)
}

void USharingUserSlot::OnUserIDButtonClicked()
{
    // 버튼 클릭 시 발생하는 이벤트, 나중에 화면 사용자를 변경하는 걸로 변경 예정
    UE_LOG(LogTemp , Log , TEXT("UserID %s Button Click") , *CurrentUserID);
}
