// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcessListButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ScreenActor.h"
#include "EngineUtils.h"

void UProcessListButton::NativeConstruct()
{
	Super::NativeConstruct();

    if ( ChangeProcessButton ) {
        ChangeProcessButton->OnClicked.AddDynamic(this , &UProcessListButton::OnChangeProcessButtonClicked);
    }

}

void UProcessListButton::OnChangeProcessButtonClicked()
{
    //버튼을 누를 시에 FindTargetWindow의 타겟을 변경
    if ( ProcessName ) {
        FString SelectedWindowTitle = ProcessName->GetText().ToString();

		// 레벨에 배치된 ScreenActor를 찾음
		TArray<AActor*> FoundActors;
		if ( UWorld* World = GEngine->GetWorldFromContextObject(GetWorld() , EGetWorldErrorMode::LogAndReturnNull) )
		{
			for ( FActorIterator It(World); It; ++It )
			{
				AActor* Actor = *It;
				if ( Actor->ActorHasTag(FName("Screen")) )
				{
					FoundActors.Add(Actor);
				}
			}
		}

        //ScreenActor의 FindTargetWindow 함수 호출
        //if( )
    }

}

//배열을 받아서 글자를 설정
void UProcessListButton::SetProcessList(FString ProgramName)
{
    if ( ProcessName )
    {
        ProcessName->SetText(FText::FromString(ProgramName));
    }
}
