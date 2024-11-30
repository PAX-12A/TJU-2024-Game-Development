/****************************************************************
 * \file   SceneManager.h
 * \brief  A manager for ground blocks and item blocks.
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SceneManager.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API USceneManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;
	UFUNCTION()
	/**
	 * \brief Generate the Ground blocks.
	 * 
	 */
	void GenerateMap();
	/**
	 * \brief Get the ground block type by location.
	 * 
	 * \param x The x location of the ground block
	 * \param y The y location of the ground block
	 * \return A FString, the type of the ground block
	 */
	FString GetGroundBlockTypeByLocation(float x, float y);
	/**
	* \brief Get the ground block temperature by location.
	* 
	* \param x The x location of the ground block
	* \param y The y location of the ground block
	* \return An int32, the temperature of the ground block
	* \throw std::out_of_range
	* 
	*/
	int32 GetGroundBlockTemperatureByLocation(float x, float y);
	/**
	 * \brief Get the index in the array of ground block at the given location.
	 * 
	 * \param x The x location of the ground block
	 * \param y The y location of the ground block
	 * \param x_index Return value. The first index of the ground block
	 * \param y_index Return value. The second index of the ground block
	 * \throw std::out_of_range
	 */
	void GetIndexOfTheGroundBlockByLocation(float x, float y, int32& x_index, int32& y_index);
	/**
	 * \brief Destroy the ground block at the given location.
	 * 
	 * \param x The x location of the ground block
	 * \param y The y location of the ground block
	 */
	void DestroyGroundBlockByLocation(float x, float y);
private:
	FTimerHandle timer_handler_;
};

