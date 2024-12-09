/*****************************************************************//**
 * \file   StardewValleyGameInstance.cpp
 * \brief  The implementation of the game instance
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#include "StardewValleyGameInstance.h"
#include "DataSystem.h"
#include "TimeSystem.h"
#include "WeatherSystem.h"
#include "SceneManager.h"
#include "UserInterface.h"

void UStardewValleyGameInstance::Init()
{
	Super::Init();

	UTimeSystem* TimeSystem = GetSubsystem<UTimeSystem>();
	UDataSystem* DataSystem = GetSubsystem<UDataSystem>();
	UWeatherSystem* WeatherSystem = GetSubsystem<UWeatherSystem>();
	USceneManager* SceneManager = GetSubsystem<USceneManager>();

	TimeSystem->set_minute(DataSystem->get_minute());
	TimeSystem->set_hour(DataSystem->get_hour());
	TimeSystem->set_day_in_season(DataSystem->get_day_in_season());
	TimeSystem->set_season(DataSystem->get_present_season());
	WeatherSystem->set_weather(DataSystem->get_present_weather());
	DataSystem->set_ground_block_x_length(128);
	DataSystem->set_ground_block_y_length(128);
	DataSystem->set_ground_block_size(200);

}
