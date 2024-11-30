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

	//Weather change
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEightInMorning.AddUObject(this, &UWeatherSystem::ChangeWeather);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEightInEvening.AddUObject(this, &UWeatherSystem::ChangeWeather);

	//Temperature change
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnHourChanged.AddUObject(this, &UWeatherSystem::UpdateBaseTemperature);
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

void UWeatherSystem::UpdateBaseTemperature()
{
	int32 current_season = GetGameInstance()->GetSubsystem<UDataSystem>()->get_present_season();
	int32 current_weather = GetGameInstance()->GetSubsystem<UDataSystem>()->get_present_weather();
	int32 current_hour = GetGameInstance()->GetSubsystem<UDataSystem>()->get_hour();

	int32 base_temperature;
	switch (current_season)
	{
	case 0:
		base_temperature = 16;
		break;
	case 1:
		base_temperature = 26;
		break;
	case 2:
		base_temperature = 11;
		break;
	case 3:
		base_temperature = 4;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("WeatherSystem.cpp: UpdateBaseTemperature: Invalid season"));
	}
	switch (current_weather)
	{
	case 0:
		base_temperature += 5;
		break;
	case 1:
		break;
	case 2:
		base_temperature -= 5;
		break;
	case 3:
		base_temperature -= 10;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("WeatherSystem.cpp: UpdateBaseTemperature: Invalid weather"));
	}

	switch (current_hour)
	{
	case 0:
	case 1:
	case 2:
		base_temperature -= 5;
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		base_temperature -= 3;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
		base_temperature -= 1;
		break;
	case 11:
	case 12:
	case 13:
	case 14:
		base_temperature += 3;
		break;
	case 15:
	case 16:
	case 17:
	case 18:
		base_temperature += 1;
		break;
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		base_temperature -= 2;
		break;
	default:
		break;
	}

	GetGameInstance()->GetSubsystem<UDataSystem>()->set_present_base_temperature(base_temperature);//datasystem update
	if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnBaseTemperatureChanged.IsBound())
		GetGameInstance()->GetSubsystem<UEventSystem>()->OnBaseTemperatureChanged.Broadcast();//broadcast
	UE_LOG(LogTemp, Warning, TEXT("Base temperature updated to %d"), base_temperature);
}