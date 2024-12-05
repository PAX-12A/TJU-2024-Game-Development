/*****************************************************************//**
 * \file   item_block_crop.cpp
 * \brief  The implementation of the item block crop
 * 
 * \author 4_of_Diamonds
 * \date   December 2024
 *********************************************************************/

#include "item_block_crop.h"
#include "EventSystem.h"
#include "DataSystem.h"
#include <stdexcept>

Aitem_block_crop::Aitem_block_crop()
{
	SetActorEnableCollision(false);
}
void Aitem_block_crop::BeginPlay()
{
	Super::BeginPlay();

	int32 x = GetActorLocation().X;
	int32 y = GetActorLocation().Y;
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index;
	int32 y_index;

	x_index = static_cast<int32>(x / block_size);
	y_index = static_cast<int32>(y / block_size);

	int32 init_status = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_status(x_index, y_index);
	if (init_status == 0)
	{
		GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_status(x_index, y_index, 1);
		init_status = 1;;
	}
	SetAppearanceByStatus(init_status);

	GetGameInstance()->GetSubsystem<UEventSystem>()->OnDayChanged.AddUObject(this, &Aitem_block_crop::Grow);

}

void Aitem_block_crop::Grow()
{
	int32 x = GetActorLocation().X;
	int32 y = GetActorLocation().Y;
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index;
	int32 y_index;

	x_index = static_cast<int32>(x / block_size);
	y_index = static_cast<int32>(y / block_size);
	int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
	int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();

	if (x < 0 || y < 0 || x_index >= x_length || y_index >= y_length)
	{
		throw std::out_of_range("Out of range");
	}

	if (is_today_watered_)
	{
		int previous_status = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_status(x_index, y_index);
		UE_LOG(LogTemp, Log, TEXT("Item block status: %d"), previous_status + 1);
		if (previous_status == lifespan_)//Time to die. Update the data system.
		{
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_type(x_index, y_index, "");
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block(y_index, x_index, nullptr);
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_status(x_index, y_index, 0);
			Destroy();
		}
		else
		{
			SetAppearanceByStatus(previous_status + 1);
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_status(x_index, y_index, previous_status + 1);
		}
		is_today_watered_ = false;
	}
}
void Aitem_block_crop::SetAppearanceByStatus(int32 status)
{
	item_mesh_->SetWorldScale3D(FVector(status, status, status) / 100.0f);
	UE_LOG(LogTemp, Log, TEXT("Item block lifespan: %d"), lifespan_);
	if (status == lifespan_)
	{
		UMaterialInterface* wither_material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/StarterContent/Materials/M_Rock_Marble_Polished.M_Rock_Marble_Polished"));
		item_mesh_->SetMaterial(0, wither_material);
	}
}
void Aitem_block_crop::WaterThisCrop()
{
	is_today_watered_ = true;
}