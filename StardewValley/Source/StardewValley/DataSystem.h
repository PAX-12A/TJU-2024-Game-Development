/****************************************************************
 * \file   DataSystem.h
 * \brief  Data system is a system to store all the data necessary.
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataSystem.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UDataSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	int32 present_season_;
	int32 day_in_season_;
	int32 hour_;
	int32 minute_;

	int32 present_weather_;
	int32 present_base_temperature_;
public:
	//Getters
	int32 get_present_season() { return present_season_; };
	int32 get_present_weather() { return present_weather_; };
	int32 get_present_base_temprature() { return present_base_temperature_; };
	int32 get_day_in_season() { return day_in_season_; };
	int32 get_hour() { return hour_; };
	int32 get_minute() { return minute_; };

	//Setters
	void set_present_season(int32 season) { present_season_ = season; };
	void set_present_weather(int32 weather) { present_weather_ = weather; };
	void set_present_base_temperature(int32 temperature) { present_base_temperature_ = temperature; };
	void set_day_in_season(int32 day) { day_in_season_ = day; };
	void set_hour(int32 hour) { hour_ = hour; };
	void set_minute(int32 minute) { minute_ = minute; };

	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;
};
