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
private:
	int32 active_item_index_;
public:
	bool Initialize() override;
public:
	UFUNCTION()
	void AddItemToShortcutBar(int32 id, int32 index);
	UFUNCTION()
	void RemoveItemFromShortcutBar(int32 index);
	/**
	 * Highlights the active item.
	 * 
	 * \param index The index of the active item
	 */
	void HighLightActiveItem(int32 index);
};
