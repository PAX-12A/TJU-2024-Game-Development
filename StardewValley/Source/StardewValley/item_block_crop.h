/*********************************************************************
 * \file   item_block_crop.h
 * \brief  The header file for item block crop
 * 
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "ItemBlockBase.h"
#include "item_block_crop.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API Aitem_block_crop : public AItemBlockBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	Aitem_block_crop();
protected:
	UPROPERTY(VisibleAnywhere)
	int32 lifespan_;
	bool is_today_watered_;
	/**
	 * Grows the crop to the next stage.
	 * 
	 */
	virtual void Grow();
	/**
	 * Sets the appearance of the crop based on its status.
	 * 
	 * \param status The status of the crop
	 */
	virtual void SetAppearanceByStatus(int32 status);
public:
	/**
	 * \brief Water the crop.
	 * 
	 */
	virtual void WaterThisCrop();
};
