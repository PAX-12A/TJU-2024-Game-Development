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
DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastDelegateTwoInt32Params, int32, int32);
DECLARE_MULTICAST_DELEGATE_FourParams(FMulticastDelegateFourParams, int32, int32, float, float);

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

	FMulticastDelegateFourParams OnItemBlockAttacked;//Give it the interaction type(int32), the damage, and the position(float, float)
	FMulticastDelegateTwoInt32Params OnGivenItems;//Give items (an int32 for the item id, an int32 for the amount) to the player(int32, int32)
};
