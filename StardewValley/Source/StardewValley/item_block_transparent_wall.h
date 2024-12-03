// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBlockBase.h"
#include "item_block_transparent_wall.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API Aitem_block_transparent_wall : public AItemBlockBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* wall_;
public:
	Aitem_block_transparent_wall();
};
