/****************************************************************
 * \file   TimeSystem.cpp
 * \brief  The implementation of the time system
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#include "TimeSystem.h"
#include "EventSystem.h"
#include <stdexcept>

void UTimeSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	FTimerDelegate timer_delegate;
	timer_delegate.BindUObject(this, &UTimeSystem::TimeFlow);
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
	if(day_in_season_ == 0)day_in_season_ = 1;
}

void UTimeSystem::TimeFlow()
{
	//UE_LOG(LogTemp, Warning, TEXT("Called"));
	Flow(1);

	//Broadcast events on key times
	if (minute_ == 0 && hour_ == 2)
	{
		if(GetGameInstance()->GetSubsystem<UEventSystem>()->OnEarlyMorningBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnEarlyMorningBegin.Broadcast();
	}
	else if (minute_ == 0 && hour_ == 6)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnMorningBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnMorningBegin.Broadcast();
	}
	else if (minute_ == 0 && hour_ == 10)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnNoonBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnNoonBegin.Broadcast();
	}
	else if (minute_ == 0 && hour_ == 14)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnAfternoonBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnAfternoonBegin.Broadcast();
	}
	else if (minute_ == 0 && hour_ == 18)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnEveningBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnEveningBegin.Broadcast();
	}
	else if (minute_ == 0 && hour_ == 22)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnNightBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnNightBegin.Broadcast();
	}

	if (season_ == Season::Spring && day_in_season_ == 1 && hour_ == 0 && minute_ == 0)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnSpringBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnSpringBegin.Broadcast();
	}
	else if (season_ == Season::Summer && day_in_season_ == 1 && hour_ == 0 && minute_ == 0)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnSummerBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnSummerBegin.Broadcast();
	}
	else if (season_ == Season::Autumn && day_in_season_ == 1 && hour_ == 0 && minute_ == 0)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnAutumnBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnAutumnBegin.Broadcast();
	}
	else if (season_ == Season::Winter && day_in_season_ == 1 && hour_ == 0 && minute_ == 0)
	{
		if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnWinterBegin.IsBound())
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnWinterBegin.Broadcast();
	}
	UE_LOG(LogTemp, Warning, TEXT("Time now is Season: %d, Day: %d, Hour: %d, minute: %d"), static_cast<int>(get_season()), get_day_in_season(), get_hour(), get_minute());
}