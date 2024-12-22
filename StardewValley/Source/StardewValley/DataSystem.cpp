/*****************************************************************//**
 * \file   DataSystem.cpp
 * \brief  The implementation of the data system
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#include "DataSystem.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TimeSystem.h"

void UDataSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

	do_save = true;
	LoadGame();
}

void UDataSystem::Deinitialize()
{
    Super::Deinitialize();
	
	if (do_save)SaveGame();
}

void UDataSystem::SaveGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (SaveGameInstance)
	{
		// Populate the save game instance with data
		SaveGameInstance->minute_ = minute_;
		SaveGameInstance->hour_ = hour_;
		SaveGameInstance->day_in_season_ = day_in_season_;
		SaveGameInstance->season_ = present_season_;
		SaveGameInstance->real_time_ = real_time_;//Time system data saved
		SaveGameInstance->weather_ = present_weather_;
		SaveGameInstance->base_temperature_ = present_base_temperature_;//Weather system data saved
		SaveGameInstance->ground_block_x_length_ = ground_block_x_length_;
		SaveGameInstance->ground_block_y_length_ = ground_block_y_length_;
		SaveGameInstance->ground_block_size_ = ground_block_size_;
		SaveGameInstance->ground_block_type_.Empty();
		SaveGameInstance->ground_block_delta_temperature_.Empty();		

		for (int i = 0; i < ground_block_x_length_ * ground_block_y_length_; i++)//Ground block data saved
		{
			SaveGameInstance->ground_block_type_.Add(ground_block_type_[i]);
			//SaveGameInstance->ground_block_delta_temperature_.Add(ground_block_delta_temperature_[i]);
		}
		SaveGameInstance->is_items_initialized_ = is_items_initialized_;
		for (int i = 0; i < item_block_lived_time_.Num(); i++)
		{
			SaveGameInstance->item_block_lived_time_.Add(item_block_lived_time_[i]);
		}
		for (int i = 0; i < item_block_durability_.Num(); i++)
		{
			SaveGameInstance->item_block_durability_.Add(item_block_durability_[i]);
		}
		for (int i = 0; i < is_item_block_watered_.Num(); i++)
		{
			SaveGameInstance->is_item_block_watered_.Add(is_item_block_watered_[i]);
		}
		for (int i = 0; i < item_block_id_.Num(); i++)//Item block data saved
		{
			SaveGameInstance->item_block_id_.Add(item_block_id_[i]);
		}
		SaveGameInstance->player_axe_level_ = player_axe_level_;
		SaveGameInstance->player_hoe_level_ = player_hoe_level_;
		SaveGameInstance->player_scythe_level_ = player_scythe_level_;
		SaveGameInstance->player_axe_exp_ = player_axe_exp_;
		SaveGameInstance->player_hoe_exp_ = player_hoe_exp_;
		SaveGameInstance->player_scythe_exp_ = player_scythe_exp_;
		for (auto it : player_bag_)//Player system data saved
		{
			SaveGameInstance->player_bag_.Add(it);
		}
		for (auto it : shortBar_)//Short bar data saved
		{
			SaveGameInstance->short_Bar_.Add(it);
		}

		// Save the data to a file
		bool bSuccess = UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SavedGame"), 0);
		if (bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Failed"));
		}
	}
}
void UDataSystem::LoadGame()
{
	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SavedGame"), 0));

	if (LoadedGame)
	{
		// Retrieve and use the loaded data
		set_minute(LoadedGame->minute_);
		set_day_in_season(LoadedGame->day_in_season_);
		set_present_season(LoadedGame->season_);
		set_hour(LoadedGame->hour_);
		set_real_time(LoadedGame->real_time_);//Time system data loaded
		set_present_weather(LoadedGame->weather_);
		set_present_base_temperature(LoadedGame->base_temperature_);// Weather system data loaded
		set_ground_block_x_length(LoadedGame->ground_block_x_length_);
		set_ground_block_y_length(LoadedGame->ground_block_y_length_);
		set_ground_block_size(LoadedGame->ground_block_size_);
		for (int i = 0; i < ground_block_x_length_ * ground_block_y_length_; i++)// Ground block data loaded
		{
			set_ground_block_type(i, LoadedGame->ground_block_type_[i]);
			//set_ground_block_delta_temperature(i, LoadedGame->ground_block_delta_temperature_[i]);
		}
		set_is_items_initialized(LoadedGame->is_items_initialized_);
		for (int i = 0; i < LoadedGame->item_block_lived_time_.Num(); i++)
		{
			set_item_block_lived_time(i, LoadedGame->item_block_lived_time_[i]);
		}
		for (int i = 0; i < LoadedGame->item_block_durability_.Num(); i++)
		{
			set_item_block_durability(i, LoadedGame->item_block_durability_[i]);
		}
		for (int i = 0; i < LoadedGame->is_item_block_watered_.Num(); i++)
		{
			set_is_item_block_watered(i, LoadedGame->is_item_block_watered_[i]);
		}
		for (int i = 0; i < LoadedGame->item_block_id_.Num(); i++)// Item block data loaded
		{
			set_item_block_id(i, LoadedGame->item_block_id_[i]);
		}
		set_player_axe_level(LoadedGame->player_axe_level_);
		set_player_hoe_level(LoadedGame->player_hoe_level_);
		set_player_scythe_level(LoadedGame->player_scythe_level_);
		set_player_axe_exp(LoadedGame->player_axe_exp_);
		set_player_hoe_exp(LoadedGame->player_hoe_exp_);
		set_player_scythe_exp(LoadedGame->player_scythe_exp_);
		for (auto it : LoadedGame->player_bag_)// Player system data loaded
		{
			player_bag_.Add(it);
		}
		for (auto it : LoadedGame->short_Bar_)// Short bar data loaded
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), it);
			shortBar_.Add(it);
		}
	}
}
