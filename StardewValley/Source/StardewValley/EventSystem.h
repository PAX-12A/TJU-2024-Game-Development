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
DECLARE_MULTICAST_DELEGATE_OneParam(FMulticastDelegateOneParam, int32);

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastDelegateTwoParams, float, float);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FMulticastDelegateThreeParams, int32, float, float)
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
	FMulticastDelegate OnGrassGroundMowed;
	FMulticastDelegate OnEarthGroundPloughed;

	FMulticastDelegateTwoParams WaterCropAtGivenPosition;//Give it the position(float, float)

	FMulticastDelegateFourParams OnItemBlockAttacked;
	FMulticastDelegateFourParams OnItemBlockInteracted;//Give it the interaction type(int32), the damage, and the position(float, float)
	FMulticastDelegateTwoInt32Params OnGivenItems;//Give items (an int32 for the item id, an int32 for the amount) to the player(int32, int32)

	FMulticastDelegate OnUIMenuClosed;//Close the UI menu
	FMulticastDelegateOneParam OnInterfaceChanged;//Give it the interface index(int32)
	FMulticastDelegate OnExitGame;//Exit the game
	FMulticastDelegate OnReturnTitle;//Return to title
	FMulticastDelegate OnAnExpBarFull;//An exp bar is full
	FMulticastDelegateTwoInt32Params OnItemAddedToShortcutBar;//Give it the item id(int32) and the index(int32) of the item in the shortcut bar
	FMulticastDelegateOneParam OnItemRemovedFromShortcutBar;//Give it the index(int32) of the item in the shortcut bar

	//Character Part
	FMulticastDelegate OnCallingMenu;//Call the menu
	/*
	FMulticastDelegate OnCharacterMenuClosed;//Close the character menu
	FMulticastDelegate OnCharacterMenuOpened;//Open the character menu
	*/
	FMulticastDelegateOneParam OnShortcutSelected;//Equip the tool
	FMulticastDelegateThreeParams OnToolsTowardsItemBlock;//Give the tool type(int32) and position(float, float) of the tool
	FMulticastDelegateThreeParams OnPlacingItem;//Give the item type(int32) and position(float, float) of the item need to be placed
	FMulticastDelegateTwoParams OnMowingGrassGround;//Give the position(float, float) of the grass to be mowed
	FMulticastDelegateTwoParams OnPloughingEarthGround;//Give the position(float, float) of the earth to be ploughed
	FMulticastDelegateTwoInt32Params OnSkillExpUpdate;//skill1->axe skill2->hoe skill3->scythe
	FMulticastDelegateOneParam OnItemUsedup;
};
