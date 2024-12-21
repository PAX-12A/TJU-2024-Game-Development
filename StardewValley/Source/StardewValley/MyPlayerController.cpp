// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "BluePrint/UserWidget.h"
void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();
	if (HUDAsset) {
		HUD = CreateWidget<UUserWidget>(this, HUDAsset);

	}
	if (HUD) {
		HUD->AddToViewport();
	}
}
