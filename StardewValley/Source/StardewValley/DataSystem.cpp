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

    UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("SavedGame"), 0));

    if (LoadedGame)
    {
        // Retrieve and use the loaded data
        set_minute(LoadedGame->minute_);
        set_day_in_season(LoadedGame->day_in_season_);
		set_present_season(LoadedGame->season_);
		set_hour(LoadedGame->hour_);//Time system data loaded
		set_present_weather(LoadedGame->weather_);
		set_present_base_temperature(LoadedGame->base_temperature_);// Weather system data loaded
		set_ground_block_x_length(LoadedGame->ground_block_x_length_);
		set_ground_block_y_length(LoadedGame->ground_block_y_length_);
		set_ground_block_size(LoadedGame->ground_block_size_);
		for (int i = 0; i < ground_block_x_length_ * ground_block_y_length_; i++)// Ground block data loaded
		{
			set_ground_block_type(i, LoadedGame->ground_block_type_[i]);
			set_ground_block_delta_temperature(i, LoadedGame->ground_block_delta_temperature_[i]);
		}
    }
}

void UDataSystem::Deinitialize()
{
    Super::Deinitialize();

    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    if (SaveGameInstance)
    {
        // Populate the save game instance with data
        SaveGameInstance->minute_ = minute_;
        SaveGameInstance->hour_ = hour_;
		SaveGameInstance->day_in_season_ = day_in_season_;
		SaveGameInstance->season_ = present_season_;//Time system data saved
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
			SaveGameInstance->ground_block_delta_temperature_.Add(ground_block_delta_temperature_[i]);
        }

        // Save the data to a file
        bool bSuccess = UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SavedGame"), 0);
        if(bSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Success"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Save Failed"));
		}
    }
}
