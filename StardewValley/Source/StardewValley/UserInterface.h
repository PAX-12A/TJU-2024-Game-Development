/*********************************************************************
 * \file   UserInterface.h
 * \brief  The header file for user interface.
 * 
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInterface.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UUserInterface : public UUserWidget
{
	GENERATED_BODY()
private:
	const float kMaxExpForEachLevel = 100.0f;
	const float kMaxLevel = 4.0f;
public:
	bool Initialize() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	//Change the interface
	/**
	 * \brief Change the interface.
	 * 
	 * \param index The index of the interface.
	 */
	void ChangeInterface(int index);
	UFUNCTION()
	void ChangeToBag() { ChangeInterface(0); }
	UFUNCTION()
	void ChangeToPlayer() { ChangeInterface(1); }
	UFUNCTION()
	void ChangeToSocial() { ChangeInterface(2); }
	UFUNCTION()
	void ChangeToCraft() { ChangeInterface(3); }
	UFUNCTION()
	void ChangeToSystem() { ChangeInterface(4); }
	UFUNCTION()
	void ChangeToDebug() { ChangeInterface(5); }
public:
	//System panel
	UFUNCTION()
	void ExitGame();
	UFUNCTION()
	void SaveGame();
	UFUNCTION()
	void ReturnToGame();
	UFUNCTION()
	void GoodbyeWorld();
	UFUNCTION()
	void ConfigOption();
public:
	//Player panel
	/**
	 * \brief Increase the progress bar value.
	 * 
	 * \param bar The progress bar.
	 * \param value The value to increase.
	 */
	void IncreaseProgressBarValue(class UProgressBar* bar, float value);
	/**
	 * \brief Set the progress bar value.
	 * 
	 * \param bar A progress bar.
	 * \param value The value to set.
	 */
	void SetProgressBarValue(class UProgressBar* bar, float value);
	void EnableALevelUpButton();
	UFUNCTION()
	void AxeLevelUp();
	UFUNCTION()
	void HoeLevelUp();
	UFUNCTION()
	void ScytheLevelUp();
	void ExpGiver(int32 type, int32 amount);
public:
	//Bag panel
	/**
	 * \brief Add an amount of item(s) to the bag.
	 * 
	 * \param id The id of the item.
	 * \param amount The amount of the item.
	 */
	void AddItemToBag(int32 id, int32 amount);
	/**
	 * \brief Remove an amount of item(s) from the bag.
	 * 
	 * \param id The id of the item.
	 * \param amount The amount of the item.
	 */
	void RemoveItemFromBag(int32 id, int32 amount);
	UFUNCTION()
	/**
	 * \brief Called when an item is selected (clicked).
	 * 
	 * \param id
	 */
	void OnItemSelected(int32 id);
	UFUNCTION()
	/**
	 * \brief Called when an item is deselected (Another item is clicked).
	 * 
	 */
	void OnItemDeselected();
	UFUNCTION()
	/**
	 * \brief Called when a shortcut is selected (Clicked).
	 * 
	 * \param index
	 */
	void OnShortcutSelected(int32 index);
	int32 item_selected_;
public:
	//Debug panel
	UFUNCTION()
	void DEBUGGER();
protected:
	TMap<int32, int32> ItemsInBag;//id -> amount
};
