// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBlockBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/DataTable.h"
#include "Struct_ItemBlockBase.h"
#include "EventSystem.h"
#include "DataSystem.h"
#include <stdexcept>

// Sets default values
AItemBlockBase::AItemBlockBase()
{
	PrimaryActorTick.bCanEverTick = true;

	item_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("item_mesh_"));
	RootComponent = item_mesh_;
	box_ = CreateDefaultSubobject<UBoxComponent>(TEXT("wall_"));
	box_->SetupAttachment(RootComponent);

}

void AItemBlockBase::InitializeItemBlock(int32 id)
{
	float x = GetActorLocation().X;
	float y = GetActorLocation().Y;
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index = static_cast<int32>(x / block_size);
	int32 y_index = static_cast<int32>(y / block_size);

	int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
	int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();
	if (x < 0 || y < 0 || x_index >= x_length || y_index >= y_length)
	{
		throw std::out_of_range("Out of range");
	}

	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_id(x_index, y_index, id);
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBlockBase.DT_ItemBlockBase"));
	FStruct_ItemBlockBase* item_info = item_data_table->FindRow<FStruct_ItemBlockBase>(FName(*FString::FromInt(id)), "");
	if (item_info != nullptr)
	{
		item_mesh_->SetStaticMesh(item_info->mesh_);
		item_mesh_->SetMaterial(0, item_info->material_);
		item_mesh_->SetWorldScale3D(FVector(item_info->scale_, item_info->scale_, item_info->scale_));
		if(GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_durability(x_index, y_index) == -1)
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_durability(x_index, y_index, item_info->durability_);

		if (item_info->type_ == 1)//crop
		{
			item_mesh_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnMinuteChanged.AddUObject(this, &AItemBlockBase::Grow);
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnWeatherChanged.AddUObject(this, &AItemBlockBase::RainWatersThisCrop);
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnDayChanged.AddUObject(this, &AItemBlockBase::GetThirsty);
			lived_time_ = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_lived_time(x_index, y_index);
			if (lived_time_ == -1)lived_time_ = 0;
			int32 accumulated_time = 0;
			//Set scale to the saved scale
			for (int32 i = 1; i <= item_info->map_lifespan_.Num(); i++)
			{
				if (item_info->map_lifespan_.Contains(i))
				{
					accumulated_time += item_info->map_lifespan_[i] * 60;
					if (lived_time_ <= accumulated_time)
					{
						SetAppearanceByStatus(i);
						break;
					}
				}
			}
			//UE_LOG(LogTemp, Warning, TEXT("Crop at %d, %d : Scale %f, %f, %f, lived time %d"), x_index, y_index, item_mesh_->GetRelativeScale3D().X, item_mesh_->GetRelativeScale3D().Y, item_mesh_->GetRelativeScale3D().Z, lived_time_);
			is_today_watered_ = GetGameInstance()->GetSubsystem<UDataSystem>()->get_is_item_block_watered(x_index, y_index);
			//UE_LOG(LogTemp, Warning, TEXT("Item block Initialized"));
		}
		else if (item_info->type_ == 2)//Architecture
		{
			item_mesh_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			item_mesh_->SetCollisionObjectType(ECC_WorldStatic);
		}
		else if (item_info->type_ == 0)//Invisible wall
		{
			box_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			box_->SetCollisionResponseToAllChannels(ECR_Block);
		}
		else if (item_info->type_ == 3)//Destroyable things
		{
			item_mesh_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			item_mesh_->SetCollisionResponseToAllChannels(ECR_Block);
		}
	}
}

void AItemBlockBase::Grow()
{
	if (!is_today_watered_)return;//No water, no growth
	float x = GetActorLocation().X;
	float y = GetActorLocation().Y;
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index = static_cast<int32>(x / block_size);
	int32 y_index = static_cast<int32>(y / block_size);

	int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
	int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();
	if (x < 0 || y < 0 || x_index >= x_length || y_index >= y_length)
	{
		throw std::out_of_range("Out of range");
	}

	lived_time_++;
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_lived_time(x_index, y_index, lived_time_);

	int32 id = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_id(x_index, y_index);
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBlockBase.DT_ItemBlockBase"));
	FStruct_ItemBlockBase* item_info = item_data_table->FindRow<FStruct_ItemBlockBase>(FName(*FString::FromInt(id)), "");
	int32 accumulated_time = 0;
	for (int32 i = 1; i <= item_info->map_lifespan_.Num(); i++)
	{
		if(item_info->map_lifespan_.Contains(i))
		{
			accumulated_time += item_info->map_lifespan_[i] * 60;
			if (lived_time_ == accumulated_time)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Crop at %d, %d grows"), x_index, y_index);
				SetAppearanceByStatus(i + 1);
				break;
			}
		}
	}
	accumulated_time = 0;
	for (auto status : item_info->map_lifespan_)
	{
		accumulated_time += status.Value * 60;
	}
	if (lived_time_ >= accumulated_time)
	{
		GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_id(x_index, y_index, -1);
		GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_lived_time(x_index, y_index, -1);
		GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block(x_index, y_index, nullptr);
		Destroy();
	}
}
void AItemBlockBase::GetThirsty()
{
	is_today_watered_ = false;
}
void AItemBlockBase::WaterThisCrop()
{
	int32 x = GetActorLocation().X;
	int32 y = GetActorLocation().Y;
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index = static_cast<int32>(x / block_size);
	int32 y_index = static_cast<int32>(y / block_size);

	is_today_watered_ = true;
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_is_item_block_watered(x_index, y_index, true);
}
void AItemBlockBase::RainWatersThisCrop()
{
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_present_weather() == 3)// If it's rainy
		WaterThisCrop();
}
void AItemBlockBase::SetAppearanceByStatus(int32 status)
{
	//UE_LOG(LogTemp, Warning, TEXT("Status: %d"), status);
	int32 x = GetActorLocation().X;
	int32 y = GetActorLocation().Y;
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index = static_cast<int32>(x / block_size);
	int32 y_index = static_cast<int32>(y / block_size);

	int32 item_id = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_id(x_index, y_index);
\
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBlockBase.DT_ItemBlockBase"));
	FStruct_ItemBlockBase* item_info = item_data_table->FindRow<FStruct_ItemBlockBase>(FName(*FString::FromInt(item_id)), "");
	
	FVector scale(1, 1, 1);
	if (item_info != nullptr)
	{
		scale = FVector(item_info->scale_, item_info->scale_, item_info->scale_);//The initial scale
	}
	auto CalculateScaleOfStatus = [scale](int32 status)->FVector
		{
			FVector temp_scale = scale;
			const float kGrowthRate = 1.25f;
			for (int32 i = 1; i < status; i++)
			{
				temp_scale *= kGrowthRate;
			}
			return temp_scale;
		};
	FVector new_scale = CalculateScaleOfStatus(status);
	item_mesh_->SetWorldScale3D(new_scale);
	//UE_LOG(LogTemp, Warning, TEXT("Scale: %f, %f, %f"), new_scale.X, new_scale.Y, new_scale.Z);
}
// Called when the game starts or when spawned
void AItemBlockBase::BeginPlay()
{
	Super::BeginPlay();

	auto GameInstance = GetGameInstance();
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance is nullptr"));
	}
	else
	{
		auto datasystem = GameInstance->GetSubsystem<UDataSystem>();
		if (datasystem == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("DataSystem is nullptr"));
		}
		else
		{
			int32 block_size = datasystem->get_ground_block_size();
			FVector extent = FVector(block_size / 2, block_size / 2, 500);
			box_->SetBoxExtent(extent);
		}
	}
}

// Called every frame
void AItemBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}