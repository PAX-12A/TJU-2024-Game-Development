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
public:
	bool Initialize() override;
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
	void ReturnToTitle();
	UFUNCTION()
	void ConfigOption();
protected:
	
};
