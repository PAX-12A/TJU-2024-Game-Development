// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "BluePrint/UserWidget.h"
void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

    ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);

    // 如果模拟触摸事件，显示鼠标光标
    if (FSlateApplication::IsInitialized() && FSlateApplication::Get().IsFakingTouchEvents())
    {
        SetShowMouseCursor(true);
    }

    // 加载并显示主菜单UI
    UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/UMG/BEGIN.BEGIN_C"));
    if (WidgetClass)
    {
        UUserWidget* MainMenu = CreateWidget<UUserWidget>(this, WidgetClass);
        if (MainMenu)
        {
            MainMenu->AddToViewport(); // 将UI添加到视口
            CurrentWidget = MainMenu;
        }
    }

    // 启用鼠标交互
    bShowMouseCursor = true;   // 显示鼠标光标
    bEnableClickEvents = true; // 启用点击事件
    bEnableTouchEvents = true; // 启用触摸事件（如果是移动设备）
    GetWorld()->GetTimerManager().SetTimer(RemoveMenuTimerHandle, this, &AMyPlayerController::RemoveWidget, 2.0f, false);


}
void AMyPlayerController::RemoveWidget()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromViewport();  // 从视口移除
        CurrentWidget = nullptr; // 清空当前小部件引用
    }
    if (HUDAsset) {
        HUD = CreateWidget<UUserWidget>(this, HUDAsset);

    }
    if (HUD) {
        HUD->AddToViewport();
    }
}