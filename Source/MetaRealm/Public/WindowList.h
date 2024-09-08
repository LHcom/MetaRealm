#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WindowList.generated.h"

/**
 * UWindowList: â ����� UI�� �������� ǥ���ϱ� ���� Ŭ����
 */
UCLASS()
class METAREALM_API UWindowList : public UUserWidget
{
	GENERATED_BODY()

public:
	// UUserWidget�� �ʱ�ȭ�� �� ȣ��Ǵ� �Լ�
	virtual void NativeConstruct() override;

	// â ����� UI�� �ʱ�ȭ�ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void InitScreenList(const TArray<FString>& WindowTitles);

protected:
	// â ��� ��ư�� �߰��ϴ� �Լ�
	void AddList(const FString& WindowTitle, int32 Index);

public:
	// UMG���� ������ GridPanel, â ��� ��ư, �� ���õ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* WindowList;

	// â ����� ǥ���� ��ư ���� ���ø�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ListButton;
};
