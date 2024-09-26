// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceedingWidget.h"

#include "MetaRealmGameState.h"
#include "ProceedStruct.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

void UProceedingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OnVisibilityChanged.AddDynamic(this, &UProceedingWidget::OnMyVisibilityChanged);
	eTxt_PageNum->OnTextCommitted.AddDynamic(this, &UProceedingWidget::OnMyPageCommit);

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
	CurrPageNum = newPageNum;
	if (newPageNum == 0)
	{
		txt_Member->SetText(FText::FromString(""));
		txt_Time->SetText(FText::FromString(""));
		txt_Condensation->SetText(FText::FromString(""));
		eTxt_PageNum->SetText(FText::FromString(FString::FromInt(CurrPageNum)));
		txt_TotalPageNum->SetText(FText::FromString(" / " + FString::FromInt(totalPageNum)));
	}
	// newPageNum의 범위가 1~totalPageNum 일때만 진행
	else if (totalPageNum >= newPageNum && newPageNum >= 1)
	{
		txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMemberList));
		txt_Time->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMeetingTime));
		txt_Condensation->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrContent));
		eTxt_PageNum->SetText(FText::FromString(FString::FromInt(CurrPageNum)));
		txt_TotalPageNum->SetText(FText::FromString(" / " + FString::FromInt(totalPageNum)));
	}
}

void UProceedingWidget::OnMyClickPrev()
{
	if (CurrPageNum - 1 <= 0)
		return;

	CurrPageNum--;
	txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMemberList));
	txt_Time->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMeetingTime));
	txt_Condensation->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrContent));
	eTxt_PageNum->SetText(FText::FromString(FString::FromInt(CurrPageNum)));
}

void UProceedingWidget::OnMyClickSubs()
{
	if (CurrPageNum + 1 > totalPageNum)
		return;

	CurrPageNum++;
	txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMemberList));
	txt_Time->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMeetingTime));
	txt_Condensation->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrContent));
	eTxt_PageNum->SetText(FText::FromString(FString::FromInt(CurrPageNum)));
}

void UProceedingWidget::OnMyPageCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		FString newPageStr = Text.ToString().TrimStartAndEnd();
		int32 newPage = FCString::Atoi(*newPageStr);
		if (newPageStr.IsEmpty() || newPage < 1 || newPage > totalPageNum)
		{
			eTxt_PageNum->SetText(FText::FromString(FString::FromInt(CurrPageNum)));
			return;
		}

		CurrPageNum = newPage;
		txt_Member->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMemberList));
		txt_Time->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrMeetingTime));
		txt_Condensation->SetText(FText::FromString(ArrRecordInfo[CurrPageNum - 1].StrContent));
		eTxt_PageNum->SetText(FText::FromString(FString::FromInt(CurrPageNum)));
	}
}
