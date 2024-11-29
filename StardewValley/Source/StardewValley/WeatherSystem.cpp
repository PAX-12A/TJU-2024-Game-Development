/*****************************************************************//**
 * \file   WeatherSystem.cpp
 * \brief  The implementation of the weather system
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#include "WeatherSystem.h"
#include "EventSystem.h"
#include "DataSystem.h"
#include <random>
#include <ctime>

void UWeatherSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	srand(time(nullptr));

	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEightInMorning.AddUObject(this, &UWeatherSystem::ChangeWeather);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEightInEvening.AddUObject(this, &UWeatherSystem::ChangeWeather);
}

void UWeatherSystem::Deinitialize()
{
	Super::Deinitialize();
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEightInMorning.RemoveAll(this);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEightInEvening.RemoveAll(this);
}

void UWeatherSystem::ChangeWeather()
{
	int32 current_weather = static_cast<int32>(weather_);
	int32 random = 0;
	//weather randomly change. Based on season
	switch (GetGameInstance()->GetSubsystem<UDataSystem>()->get_present_season())
	{
	case 0:
		random = rand() % 10;
		if (random < 4)current_weather = 0;
		else if (random < 7)current_weather = 1;
		else current_weather = 2;
		break;
	case 1:
		random = rand() % 100;
		if (random < 30)current_weather = 0;
		else if (random < 55)current_weather = 1;
		else current_weather = 2;
		break;
	case 2:
		random = rand() % 10;
		if (random < 5)current_weather = 0;
		else if (random < 8)current_weather = 1;
		else current_weather = 2;
		break;
	case 3:
		random = rand() % 100;
		if (random < 60)current_weather = 0;
		else if (random < 85)current_weather = 1;
		else current_weather = 3;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("WeatherSystem.cpp: ChangeWeather: Invalid season"));
	}

	GetGameInstance()->GetSubsystem<UDataSystem>()->set_present_weather(current_weather);//datasystem update
	weather_ = static_cast<Weather>(current_weather);
	if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnWeatherChanged.IsBound())
		GetGameInstance()->GetSubsystem<UEventSystem>()->OnWeatherChanged.Broadcast();//broadcast

	UE_LOG(LogTemp, Warning, TEXT("Weather changed to %d"), static_cast<int32>(weather_));
}