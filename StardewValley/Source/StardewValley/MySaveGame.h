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
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 ground_block_x_length_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 ground_block_y_length_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<FString> ground_block_type_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<int32> ground_block_delta_temperature_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 ground_block_size_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<int32> item_block_id_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	bool is_items_initialized_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<int32> item_block_lived_time_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<int32> item_block_durability_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<bool> is_item_block_watered_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 real_time_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 player_axe_level_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 player_hoe_level_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 player_scythe_level_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 player_axe_exp_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 player_hoe_exp_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 player_scythe_exp_;
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TMap<int32, int32> player_bag_;
};
