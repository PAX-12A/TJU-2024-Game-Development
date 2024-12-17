// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************************
 * \file   CharacterManager.h
 * \brief  The Definition of the character manager class
 *
 * \author magician
 * \date   December 2024
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CharacterManager.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UCharacterManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void CharacterGenerate();
};
