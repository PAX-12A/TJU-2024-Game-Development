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
	int32 present_weather_;
public:
	//Getters
	int32 get_present_season() { return present_season_; };
	int32 get_present_weather() { return present_weather_; };

	//Setters
	void set_present_season(int32 season) { present_season_ = season; };
	void set_present_weather(int32 weather) { present_weather_ = weather; };
};
