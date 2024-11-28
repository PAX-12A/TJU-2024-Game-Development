// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSystem.h"
#include <stdexcept>

void UTimeSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FTimerDelegate timer_delegate;
	timer_delegate.BindUObject(this, &UTimeSystem::TimeFlow);
	UE_LOG(LogTemp, Warning, TEXT("Time now is Season"));
	GetGameInstance()->GetWorld()->GetTimerManager().SetTimer(timer_handle_, timer_delegate, 1.0f, true);
}

void UTimeSystem::Deinitialize()
{
	Super::Deinitialize();

	// Get the game instance and then the world
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UWorld* World = GameInstance->GetWorld();
		if (World)
		{
			// Clear the timer
			World->GetTimerManager().ClearTimer(timer_handle_);
		}
	}
}

void UTimeSystem::Flow(const int32 kElapsedTimeInMinutes)
{
	if (kElapsedTimeInMinutes < 0)
	{
		throw std::invalid_argument("We don't go back in time!");
	}
	minute_ += kElapsedTimeInMinutes;

	hour_ += minute_ / kMinutesInHour;
	minute_ = minute_ % kMinutesInHour;

	day_in_season_ += hour_ / kHoursInDay;
	hour_ = hour_ % kHoursInDay;

	int elapsed_seasons = day_in_season_ / kDaysInSeason;
	int final_season = static_cast<int>(season_) + elapsed_seasons;
	season_ = static_cast<Season>(final_season % kSeasonsNum);
	day_in_season_ = day_in_season_ % kDaysInSeason;
}

void UTimeSystem::TimeFlow()
{
	//UE_LOG(LogTemp, Warning, TEXT("Called"));
	Flow(1);
	UE_LOG(LogTemp, Warning, TEXT("Time now is Season: %d, Day: %d, Hour: %d, minute: %d"), static_cast<int>(get_season()), get_day_in_season(), get_hour(), get_minute());
}
