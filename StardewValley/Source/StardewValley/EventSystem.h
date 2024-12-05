/*****************************************************************
 * \file   EventSystem.h
 * \brief  The EventSystem. Use for communication between different parts.
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventSystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FMulticastDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastDelegateTwoParams, float, float);

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UEventSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	FMulticastDelegate OnEarlyMorningBegin;
	FMulticastDelegate OnMorningBegin;
	FMulticastDelegate OnNoonBegin;
	FMulticastDelegate OnAfternoonBegin;
	FMulticastDelegate OnEveningBegin;
	FMulticastDelegate OnNightBegin;
	FMulticastDelegate OnSpringBegin;
	FMulticastDelegate OnSummerBegin;
	FMulticastDelegate OnAutumnBegin;
	FMulticastDelegate OnWinterBegin;
	FMulticastDelegate OnEightInMorning;//For weather to change
	FMulticastDelegate OnEightInEvening;//For weather to change
	FMulticastDelegate OnHourChanged;
	FMulticastDelegate OnDayChanged;
	FMulticastDelegate OnSeasonChanged;
	FMulticastDelegate OnMinuteChanged;

	FMulticastDelegate OnWeatherChanged;
	FMulticastDelegate OnBaseTemperatureChanged;

	FMulticastDelegate OnGroundGenerated;

	FMulticastDelegateTwoParams WaterCropAtGivenPosition;
};
