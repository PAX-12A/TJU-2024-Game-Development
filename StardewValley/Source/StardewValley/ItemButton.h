/*********************************************************************
 * \file   ItemButton.h
 * \brief  To pass parameter on event.
 * 
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "ItemButton.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParam, int32);


/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UItemButton : public UButton
{
	GENERATED_BODY()
	
public:
	UItemButton();
	FMulticastDelegateOneParam OnItemSelected;
	FMulticastDelegateOneParam OnShortcutSelected;
	UFUNCTION()
	void OnClick();
};
