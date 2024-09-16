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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeOnInitialized();


public:
	// UMG���� ������ GridPanel, â ��� ��ư, �� ���õ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* WindowList;

	// â ����� ǥ���� ��ư ���� ���ø�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SharingUserSlotFactory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UUserWidget* SharingUserSlot; //����� ������ ǥ���ϴ� ����

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ButtonWindowScreen; //ȭ�� ���� �����ϰų� �����ϴ� ��ư
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ButtonLookSharingScreen; //�ٸ� ������� ����ȭ���� �� �� �ֵ��� ����
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextWindowScreen; //ButtonWindowScreen�� ���¸� ǥ��. ���� �߿��� ����, �ƴҶ��� ȭ�����
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextLookSharingScreen; //ButtonLookSharingScreen�� ���¸� ǥ��. ���� ���϶��� ������, �ƴ� ���� ȭ�麸��

	UPROPERTY(meta = (BindWidget))
    class UImage* ImageSharingScreen; //������ ȭ���� ǥ���� �̹���

	class AScreenActor* ScreenActor;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImageCoveringScreen; //ȭ���� ���� �̹�����, ���� ȭ���� �����ų� Ư�� ���¿��� �����ִ� ����
	
	bool bStreaming; //���� ȭ���� ����  ������
	bool bLookStreaming; // ������ ȭ�� ���� ��Ʈ���Ӹ� ��Ÿ��. �ȼ� ��Ʈ������ ���� ȭ���� ������ �� �ش� ��Ʈ���� ��ü�� ����

	TSharedPtr<class IPixelStreamingStreamer> CurrentStreamer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capture", meta = (AllowPrivateAccess = "true"))
    class USceneCaptureComponent2D* SceneCapture; //ȭ���� ĸ���ϴ� ��� ĸ�� ������Ʈ
    // Render target to store captured scene

    // Pixel Streaming video input from render target
	//�ȼ� ��Ʈ���ֿ� ���Ǵ� ���� �Է� �ҽ�, ���� Ÿ���� ����ؼ� ȭ���� ��Ʈ������
    TSharedPtr<class FPixelStreamingVideoInputRenderTarget> VideoInput; 
	
public:

	//�־��� ID�� ����Ͽ� ScreenActor�� ���� ����� ID ����
	UFUNCTION()
	void SetUserID(FString ID); 

	// ��ư�� ������ ��, ȣ��� ��������Ʈ�� ����� �Լ�
	//ȭ�� ���� ��ư�� Ŭ���� �� ȣ��, �ȼ� ��Ʈ������ ����
	UFUNCTION(BlueprintCallable)
	void OnButtonWindowScreen();
	//�ٸ� ������� ���� ȭ���� ���� ���
	UFUNCTION(BlueprintCallable)
	void OnButtonLookSharingScreen();
	
	void SetScreenActor(class AScreenActor* Actor);
	//���� �¶��� ������ ID ��ȯ
	FString GetCurrentSessionID();

	//���� ����� ������ �ʱ�ȭ
	void InitSlot(TArray<FString> Items);
};
