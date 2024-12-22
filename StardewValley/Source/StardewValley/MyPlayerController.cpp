// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "BluePrint/UserWidget.h"
void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

    ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);

    // ���ģ�ⴥ���¼�����ʾ�����
    if (FSlateApplication::IsInitialized() && FSlateApplication::Get().IsFakingTouchEvents())
    {
        SetShowMouseCursor(true);
    }

    // ���ز���ʾ���˵�UI
    UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/UMG/BEGIN.BEGIN_C"));
    if (WidgetClass)
    {
        UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, WidgetClass);
        if (MainMenu)
        {
            MainMenu->AddToViewport(); // ��UI��ӵ��ӿ�
            CurrentWidget = MainMenu;
        }
    }

    // ������꽻��
    bShowMouseCursor = true;   // ��ʾ�����
    bEnableClickEvents = true; // ���õ���¼�
    bEnableTouchEvents = true; // ���ô����¼���������ƶ��豸��
    GetWorld()->GetTimerManager().SetTimer(RemoveMenuTimerHandle, this, &AMyPlayerController::RemoveWidget, 2.0f, false);


}
void AMyPlayerController::RemoveWidget()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromViewport();  // ���ӿ��Ƴ�
        CurrentWidget = nullptr; // ��յ�ǰС��������
    }
    if (HUDAsset) {
        HUD = CreateWidget<UUserWidget>(this, HUDAsset);

    }
    if (HUD) {
        HUD->AddToViewport();
    }
}