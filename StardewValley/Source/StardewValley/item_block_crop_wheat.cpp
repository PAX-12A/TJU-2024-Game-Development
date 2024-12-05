/*****************************************************************//**
 * \file   item_block_crop_wheat.cpp
 * \brief  The implementation of the item block crop wheat
 * 
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/

#include "item_block_crop_wheat.h"

Aitem_block_crop_wheat::Aitem_block_crop_wheat()
{
}

void Aitem_block_crop_wheat::BeginPlay()
{
	Super::BeginPlay();

	lifespan_ = 3;
}
