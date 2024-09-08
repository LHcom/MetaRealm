// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowList.h"

void UWindowList::NativeConstruct()
{
}

void UWindowList::InitScreenList(const TArray<FString>& WindowTitles)
{
    if (WindowList && ListButton)
    {
        // 리스트를 초기화
        WindowList->ClearChildren();

        // 창 제목 수만큼 버튼을 생성
        for (int32 i = 0; i < WindowTitles.Num(); i++)
        {
            AddList(WindowTitles[i], i);
        }
    }
}

void UWindowList::AddList(const FString& WindowTitle, int32 Index)
{
    // 버튼을 생성하고 리스트에 추가
    UUserWidget* NewButton = CreateWidget<UUserWidget>(this, ListButton);
    if (NewButton)
    {
        // 버튼에 텍스트 설정 (여기서는 ListButton의 TextBlock을 찾는다고 가정)
        UTextBlock* ButtonText = Cast<UTextBlock>(NewButton->GetWidgetFromName(TEXT("ButtonText")));
        if (ButtonText)
        {
            ButtonText->SetText(FText::FromString(WindowTitle));
        }

        // 버튼을 Grid에 추가
        WindowList->AddChildToUniformGrid(NewButton, 0, Index); // 2열로 정렬한다고 가정
    }
}
