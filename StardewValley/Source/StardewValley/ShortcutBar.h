// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShortcutBar.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UShortcutBar : public UUserWidget
{
	GENERATED_BODY()
public:
	bool Initialize() override;
public:
	UFUNCTION()
	void AddItemToShortcutBar(int32 id, int32 index);
	UFUNCTION()
	void RemoveItemFromShortcutBar(int32 index);
};
