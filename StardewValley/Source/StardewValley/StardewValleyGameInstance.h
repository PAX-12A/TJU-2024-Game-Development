// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StardewValleyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UStardewValleyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

};
