// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBlockBase.h"
#include "item_block_tree.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API Aitem_block_tree : public AItemBlockBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* foliage_mesh_;
public:
	Aitem_block_tree();
};
