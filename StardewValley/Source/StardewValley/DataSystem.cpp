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
		set_hour(LoadedGame->hour_);
		set_present_weather(LoadedGame->weather_);
		set_present_base_temperature(LoadedGame->base_temperature_);
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
		SaveGameInstance->season_ = present_season_;
		SaveGameInstance->weather_ = present_weather_;
        SaveGameInstance->base_temperature_ = present_base_temperature_;


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
