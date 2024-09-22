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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeOnInitialized();


public:
	// UMG에서 가져올 GridPanel, 창 목록 버튼, 및 관련된 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* WindowList;

	// 창 목록을 표시할 버튼 위젯 템플릿
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> SharingUserSlotFactory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USharingUserSlot* SharingUserSlot; //사용자 정보를 표시하는 슬롯

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ButtonWindowScreen; //화면 공유 시작하거나 중지하는 버튼
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* ButtonLookSharingScreen; //다른 사용자의 공유화면을 볼 수 있도록 설정
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextWindowScreen; //ButtonWindowScreen의 상태를 표시. 공유 중에는 공유, 아닐때는 화면공유
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TextLookSharingScreen; //ButtonLookSharingScreen의 상태를 표시. 보는 중일때는 보는중, 아닐 때는 화면보기

	UPROPERTY(meta = (BindWidget))
    class UImage* ImageSharingScreen; //공유된 화면을 표시할 이미지

	class AScreenActor* ScreenActor;

	UPROPERTY(meta = (BindWidget))
	class UImage* ImageCoveringScreen; //화면을 덮는 이미지로, 공유 화면을 가리거나 특정 상태에서 보여주는 역할
	
	bool bStreaming; //현재 화면을 공유  중인지
	bool bLookStreaming; // 현재의 화면 공유 스트리머를 나타냄. 픽셀 스트리밍을 통해 화면을 공유할 때 해당 스트리머 객체가 사용됨

	TSharedPtr<class IPixelStreamingStreamer> CurrentStreamer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Capture", meta = (AllowPrivateAccess = "true"))
    class USceneCaptureComponent2D* SceneCapture; //화면을 캡쳐하는 장면 캡쳐 컴포넌트
    // Render target to store captured scene

    // Pixel Streaming video input from render target
	//픽셀 스트리밍에 사용되는 비디오 입력 소스, 렌더 타겟을 사용해서 화면을 스트리밍함
    TSharedPtr<class FPixelStreamingVideoInputRenderTarget> VideoInput; 
	
public:

	//주어진 ID를 사용하여 ScreenActor의 공유 사용자 ID 설정
	UFUNCTION()
	void SetUserID(FString ID, const bool& bAddPlayer); 

	// 버튼을 눌렀을 때, 호출될 델리게이트에 등록할 함수
	//화면 공유 버튼을 클릭할 때 호출, 픽셀 스트리밍을 시작
	UFUNCTION(BlueprintCallable)
	void OnButtonWindowScreen();
	//다른 사용자의 공유 화면을 보는 기능
	UFUNCTION(BlueprintCallable)
	void OnButtonLookSharingScreen();
	
	void SetScreenActor(class AScreenActor* Actor);
	//현재 온라인 세션의 ID 반환
	FString GetCurrentSessionID();

	//여러 사용자 슬롯을 초기화
	void InitSlot(TArray<FString> Items);


public:
	//==========특정 화면 공유 부분
	//UPROPERTY(EditAnywhere , BlueprintReadWrite , meta = (BindWidget))
	//class UUniformGridPanel* ProcessList; //현재 자신의 컴에서 실행되고 있는 창의 목록을 넣을 패널

	//// 현재 켜져있는 프로세스 목록을 표시할 버튼 위젯 템플릿
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<UUserWidget> ProcessListButtonFactory;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UProcessListButton* ProcessListButtonSlot; //사용자 정보를 표시하는 슬롯

	////화면 공유가 있는 레벨에 들어갔을 경우 곧바로 프로세스 리스트가 뜸.

	////Grid 패널에 프로세스 리스트UI를 현재 프로세스 창만큼의 수를 채우는 함수
	//void InitProcessListUI();

private:
	UPROPERTY()
	class APlayerCharacter* Me;
};
