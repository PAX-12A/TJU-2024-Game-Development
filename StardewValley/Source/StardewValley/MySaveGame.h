/****************************************************************
 * \file   MySaveGame.h
 * \brief  Saves and loads game data
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 minute_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 hour_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 day_in_season_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 season_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 weather_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 base_temperature_;
};