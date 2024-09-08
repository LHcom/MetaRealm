#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WindowList.generated.h"

/**
 * UWindowList: 창 목록을 UI에 동적으로 표시하기 위한 클래스
 */
UCLASS()
class METAREALM_API UWindowList : public UUserWidget
{
	GENERATED_BODY()

public:
	// UUserWidget이 초기화될 때 호출되는 함수
	virtual void NativeConstruct() override;

	// 창 목록을 UI에 초기화하는 함수
	UFUNCTION(BlueprintCallable)
	void InitScreenList(const TArray<FString>& WindowTitles);

protected:
	// 창 목록 버튼을 추가하는 함수
	void AddList(const FString& WindowTitle, int32 Index);

public:
	// UMG에서 가져올 GridPanel, 창 목록 버튼, 및 관련된 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* WindowList;

	// 창 목록을 표시할 버튼 위젯 템플릿
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ListButton;
};
