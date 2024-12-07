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
	//Ground Blocks
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
	/**
	 * \brief Create the ground block of the given type at the given location.
	 * \brief The ground block will be destroyed if it already exists.
	 * \brief The ground block must be within the 128x128 grid.
	 * 
	 * \param x the x location of the ground block
	 * \param y the y location of the ground block
	 * \param type the type of the ground block
	 */
	void CreateGroundBlockByLocation(float x, float y, FString type);
	/**
	 * \brief Change all the earth ground to snow ground. Called when winter starts.
	 * 
	 */
	void ChangeEarthGroundToSnowGround();
	/**
	 * \brief Change all the snow ground to earth ground. Called when spring starts.
	 * 
	 */
	void ChangeSnowGroundToEarthGround();

	//Item Blocks
	/**
	 * \brief Create the item block of the given class at the given location.
	 * 
	 * \param x The x location of the item block
	 * \param y The y location of the item block
	 * \param id The id of the item
	 */
	void CreateItemBlockByLocation(float x, float y, int32 id);
	/**
	 * \brief Destroy the item block at the given location.
	 * 
	 * \param x The x location of the item block
	 * \param y The y location of the item block
	 */
	void DestroyItemBlockByLocation(float x, float y);
	/**
	 * \brief Generate the items.
	 * 
	 */
	void GenerateItems();
	/**
	 * \brief Waters the crop at the given location.
	 * 
	 * \param x The x location of the crop
	 * \param y The y location of the crop
	 */
	void WaterCropAtLocation(float x, float y);
	/**
	 * \brief Handles the interaction.
	 * 
	 * \param interaction_type The type of the interaction, an int32
	 * \param x The x location of the interaction, a float
	 * \param y The y location of the interaction, a float
	 */
	void ItemBlockInteractionHandler(int32 interaction_type, int32 damage, float x, float y);

	UClass* TypeToClass(FString type);
	struct item_size { int32 x_length; int32 y_length; };
	TMap<FString, item_size> TypeToSizeMap;
private:
	FTimerHandle timer_handler_;
	const int kMaxLength = 128;
	const int kDefaultBlockSize = 200;
	const int kHeight = 0;
};

