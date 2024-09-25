// Fill out your copyright notice in the Description page of Project Settings.


#include "SharingUserSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ScreenActor.h"
#include "EngineUtils.h"
#include "WindowList.h"

void USharingUserSlot::NativeConstruct()
{
    Super::NativeConstruct();

    // 레벨에 배치된 ScreenActor를 찾음
    for ( TActorIterator<AScreenActor> It(GetWorld() , AScreenActor::StaticClass()); It; ++It )
    {
        ScreenActor = *It;
        break;
    }

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
    // 버튼 클릭 시 발생하는 이벤트, 다른 스트리머의 화면을 볼 수 있어야함
    //아이디 전환
    //ScreenActor->ChangeLookSharingScreen();

    WindowList->OnButtonLookSharingScreen();

}
