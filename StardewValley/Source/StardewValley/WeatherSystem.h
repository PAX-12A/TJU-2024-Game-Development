/****************************************************************
 * \file   WeatherSystem.h
 * \brief  The system to control the weather and broadcast weather information.
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeatherSystem.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UWeatherSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	enum class Weather
	{
		Sunny,
		Cloudy,
		Rainy,
		Snowy
	};
	Weather weather_;
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;
	void ChangeWeather();
};
