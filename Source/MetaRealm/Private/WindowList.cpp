// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowList.h"

void UWindowList::NativeConstruct()
{
}

void UWindowList::InitScreenList(const TArray<FString>& WindowTitles)
{
    if (WindowList && ListButton)
    {
        // ����Ʈ�� �ʱ�ȭ
        WindowList->ClearChildren();

        // â ���� ����ŭ ��ư�� ����
        for (int32 i = 0; i < WindowTitles.Num(); i++)
        {
            AddList(WindowTitles[i], i);
        }
    }
}

void UWindowList::AddList(const FString& WindowTitle, int32 Index)
{
    // ��ư�� �����ϰ� ����Ʈ�� �߰�
    UUserWidget* NewButton = CreateWidget<UUserWidget>(this, ListButton);
    if (NewButton)
    {
        // ��ư�� �ؽ�Ʈ ���� (���⼭�� ListButton�� TextBlock�� ã�´ٰ� ����)
        UTextBlock* ButtonText = Cast<UTextBlock>(NewButton->GetWidgetFromName(TEXT("ButtonText")));
        if (ButtonText)
        {
            ButtonText->SetText(FText::FromString(WindowTitle));
        }

        // ��ư�� Grid�� �߰�
        WindowList->AddChildToUniformGrid(NewButton, 0, Index); // 2���� �����Ѵٰ� ����
    }
}
