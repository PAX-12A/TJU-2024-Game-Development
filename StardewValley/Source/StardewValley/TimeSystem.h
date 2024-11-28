/*****************************************************************
 * \file   TimeSystem.h
 * \brief  The time system of the stardew valley. 1 minute in game is 1 second in real life.
 * \brief  A day is devided into early_morning, morning, noon, afternoon, evening and night.
 * \brief  A year is devided into spring, summer autumn and winter. And it's 30 days for each season.
 *
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeSystem.generated.h"

 /**
  *
  */
UCLASS()
class STARDEWVALLEY_API UTimeSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	/**
	* The seasons.
	*/
	enum class Season
	{
		Spring,
		Summer,
		Autumn,
		Winter
	};
	const int kDaysInSeason = 31;
	const int kHoursInDay = 24;
	const int kMinutesInHour = 60;
	const int kSeasonsNum = 4;

	Season season_;
	int32 day_in_season_;
	int32 hour_;
	int32 minute_;

	FTimerHandle timer_handle_;
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
public:
	// Getters
	Season get_season() { return season_; }
	int get_day_in_season() { return day_in_season_; }
	int get_hour() { return hour_; }
	int get_minute() { return minute_; }

	// Setters
	void set_season(int32 season) { season_ = static_cast<Season>(season); }
	void set_day_in_season(int32 day_in_season) { day_in_season_ = day_in_season; }
	void set_hour(int32 hour) { hour_ = hour; }
	void set_minute(int32 minute) { minute_ = minute; }

	/**
	 * \brief To have the time flow by given minutes, 1 minute by default.
	 *
	 * \param kElapsedTimeInMinutes The number of minutes to flow.
	 * \throw invalid_argument exception when the number of minutes is negative.
	 */
	void Flow(const int32 kElapsedTimeInMinutes = 1);

	UFUNCTION()
	void TimeFlow();
};
