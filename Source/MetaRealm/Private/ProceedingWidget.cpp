// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceedingWidget.h"

#include "JsonParseLib.h"
#include "MetaRealmGameState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UProceedingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnVisibilityChanged.AddDynamic(this, &UProceedingWidget::OnMyVisibilityChanged);
	btn_Close->OnClicked.AddDynamic(this, &UProceedingWidget::OnMyClose);
	btn_Prev->OnClicked.AddDynamic(this, &UProceedingWidget::OnMyClickPrev);
	btn_Subs->OnClicked.AddDynamic(this, &UProceedingWidget::OnMyClickSubs);
}

void UProceedingWidget::OnMyClose()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UProceedingWidget::OnMyVisibilityChanged(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Visible)
	{
		if (!GS)
			GS = Cast<AMetaRealmGameState>(GetWorld()->GetGameState());

		if (!GS)
			return;

		ArrRecordInfo = GS->ArrRecordInfo;
		totalPageNum = ArrRecordInfo.Num();
		SetCurrPage(totalPageNum);
	}
}

void UProceedingWidget::SetCurrPage(int32 newPageNum)
{
	// newPageNum의 범위가 1~totalPageNum 일때만 진행
	if (totalPageNum >= newPageNum && newPageNum >= 1)
	{
		CurrPageNum = newPageNum;
		
		txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum-1].StrMemberList));
		txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum-1].StrMeetingTime));
		txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum-1].StrContent));
	}
}

void UProceedingWidget::OnMyClickPrev()
{
}

void UProceedingWidget::OnMyClickSubs()
{
}
