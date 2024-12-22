/*****************************************************************//**
 * \file   SceneManager.cpp
 * \brief  The implementation of the scene manager
 *
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#include "SceneManager.h"
#include "GrassGround.h"
#include "DataSystem.h"
#include "EventSystem.h"
#include <stdexcept>
#include "ItemBlockBase.h"
#include "Engine/DataTable.h"
#include "Struct_ItemBlockBase.h"
#include "UserInterface.h"
#include <random>
#include <ctime>


void USceneManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	srand(time(nullptr));
	is_menu_exist = false;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(timer_handler_, this, &USceneManager::GenerateMap, 2.0f, false);
	}
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnGroundGenerated.AddUObject(this, &USceneManager::GenerateItems);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnWinterBegin.AddUObject(this, &USceneManager::ChangeEarthGroundToSnowGround);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnSpringBegin.AddUObject(this, &USceneManager::ChangeSnowGroundToEarthGround);
	GetGameInstance()->GetSubsystem<UEventSystem>()->WaterCropAtGivenPosition.AddUObject(this, &USceneManager::WaterCropAtLocation);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnItemBlockInteracted.AddUObject(this, &USceneManager::ItemBlockInteractionHandler);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnCallingMenu.AddUObject(this, &USceneManager::InvokeUIMenu);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnUIMenuClosed.AddUObject(this, &USceneManager::SetIsMenuExistToFalse);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnMowingGrassGround.AddUObject(this, &USceneManager::ChangeGrassGroundToEarthGround);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnPloughingEarthGround.AddUObject(this, &USceneManager::ChangeEarthGroundToFieldGround);
}

void USceneManager::Deinitialize()
{
	Super::Deinitialize();

	// Get the game instance and then the world
	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		UWorld* World = GameInstance->GetWorld();
		if (World)
		{
			// Clear the timer
			World->GetTimerManager().ClearTimer(timer_handler_);
		}
	}
}

void USceneManager::GenerateMap()
{
	// The World context
	UWorld* World = GetWorld();
	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	// Load the blueprint class
	UClass* GrassGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_GrassGround.BP_GrassGround_C"));
	UClass* EarthGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_EarthGround.BP_EarthGround_C"));
	UClass* FieldGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_FieldGround.BP_FieldGround_C"));
	UClass* SnowGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_SnowGround.BP_SnowGround_C"));
	UClass* WaterGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_WaterGround.BP_WaterGround_C"));
	TArray<UClass*> GroundClasses = { GrassGroundClass, EarthGroundClass, FieldGroundClass, SnowGroundClass, WaterGroundClass };

	if (GrassGroundClass)
	{
		int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
		int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();
		int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();

		//If there is no ground block, create the initial map.
		if (GetGameInstance()->GetSubsystem<UDataSystem>()->is_items_initialized() == false)
		{
			x_length = kMaxLength;
			y_length = kMaxLength;
			block_size = kDefaultBlockSize;
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_x_length(x_length);
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_y_length(y_length);
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_size(block_size);

			for (int i = 0; i < x_length * y_length; i++)
			{
				GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, "GrassGround");
				GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(i, 0);
			}

			for (int i = 0; i <= 71; i++)
				for (int j = 99; j <= 127; j++)
				{
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, j, "WaterGround");
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(i, j, 0);
				}
			for (int i = 32; i <= 83; i++)
				for (int j = 43; j <= 89; j++)
				{
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, j, "FieldGround");
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(i, j, 0);
				}
			for (int i = 29; i <= 88; i++)
				for (int j = 29; j <= 37; j++)
				{
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, j, "EarthGround");
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(i, j, 0);
				}
			for (int i = 89; i <= 97; i++)
				for (int j = 29; j <= 92; j++)
				{
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, j, "EarthGround");
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(i, j, 0);
				}
		}
		AActor* GroundInstance = nullptr;
		// Spawn the ground
		for (int i = 0; i < x_length; i++)
		{
			for (int j = 0; j < y_length; j++)
			{
				int32 type_index = 0;
				FString type = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_type(i * x_length + j);
				if (type == "GrassGround")type_index = 0;
				else if (type == "EarthGround")type_index = 1;
				else if (type == "FieldGround")type_index = 2;
				else if (type == "SnowGround")type_index = 3;
				else if (type == "WaterGround")type_index = 4;
				else continue;
				GroundInstance = World->SpawnActor<AActor>(GroundClasses[type_index], SpawnLocation + FVector(i * block_size, j * block_size, 0.0f), SpawnRotation);
				GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block(i * x_length + j, Cast<AGroundBlockBase>(GroundInstance));
			}
		}

		if (GroundInstance)
		{
			if (GetGameInstance()->GetSubsystem<UEventSystem>()->OnGroundGenerated.IsBound())
				GetGameInstance()->GetSubsystem<UEventSystem>()->OnGroundGenerated.Broadcast();
			UE_LOG(LogTemp, Warning, TEXT("Ground instance created successfully!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create Ground instance!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load BP_GrassGround class!"));
	}
}

/*----------------------------------------------Ground Block-------------------------------------*/
FString USceneManager::GetGroundBlockTypeByLocation(float x, float y)
{
	int32 index_x, index_y;
	try
	{
		GetIndexOfTheGroundBlockByLocation(x, y, index_x, index_y);
	}
	catch (const std::out_of_range& e)
	{
		UE_LOG(LogTemp, Error, TEXT("SceneManager.cpp: DestroyGroundBlockByLocation: %s"), *FString(e.what()));
		return "";
	}
	return GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_type(index_x, index_y);
}
int32 USceneManager::GetGroundBlockTemperatureByLocation(float x, float y)
{
	int32 index_x, index_y;
	try
	{
		GetIndexOfTheGroundBlockByLocation(x, y, index_x, index_y);
	}
	catch (const std::out_of_range& e)
	{
		UE_LOG(LogTemp, Error, TEXT("SceneManager.cpp: DestroyGroundBlockByLocation: %s"), *FString(e.what()));
		throw std::out_of_range("Out of range");
	}
	int32 base_temperature = GetGameInstance()->GetSubsystem<UDataSystem>()->get_present_base_temperature();
	int32 delta_temperature = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_delta_temperature(index_x, index_y);
	return base_temperature + delta_temperature;
}
void USceneManager::GetIndexOfTheGroundBlockByLocation(float x, float y, int32& x_index, int32& y_index)
{
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	x_index = static_cast<int32>(x / block_size);
	y_index = static_cast<int32>(y / block_size);
	int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
	int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();

	if (x < 0 || y < 0 || x_index >= x_length || y_index >= y_length)
	{
		throw std::out_of_range("Out of range");
	}
}
void USceneManager::DestroyGroundBlockByLocation(float x, float y)
{
	int32 index_x, index_y;
	try
	{
		GetIndexOfTheGroundBlockByLocation(x, y, index_x, index_y);
	}
	catch (const std::out_of_range& e)
	{
		UE_LOG(LogTemp, Error, TEXT("SceneManager.cpp: DestroyGroundBlockByLocation: %s"), *FString(e.what()));
		return;
	}
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(index_x, index_y, "");
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(index_x, index_y, 0);
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block(index_x, index_y) == nullptr)return;
	bool is_destroyed = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block(index_x, index_y)->Destroy();
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block(index_x, index_y, nullptr);
}
void USceneManager::CreateGroundBlockByLocation(float x, float y, FString type)
{
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index = static_cast<int32>(x / block_size);
	int32 y_index = static_cast<int32>(y / block_size);
	int32 x_length = kMaxLength;
	int32 y_length = kMaxLength;

	if (x < 0 || y < 0 || x_index >= x_length || y_index >= y_length)
	{
		throw std::out_of_range("Out of range");
	}

	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block(x_index, y_index) != nullptr)//There is already a ground block
	{
		DestroyGroundBlockByLocation(x, y);
	}

	// Load the blueprint class
	UClass* GrassGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_GrassGround.BP_GrassGround_C"));
	UClass* EarthGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_EarthGround.BP_EarthGround_C"));
	UClass* FieldGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_FieldGround.BP_FieldGround_C"));
	UClass* SnowGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_SnowGround.BP_SnowGround_C"));
	UClass* WaterGroundClass = LoadObject<UClass>(nullptr, TEXT("/Game/GroundBlock/BP_WaterGround.BP_WaterGround_C"));
	TArray<UClass*> GroundClasses = { GrassGroundClass, EarthGroundClass, FieldGroundClass, SnowGroundClass, WaterGroundClass };

	// For each type of ground block
	int type_index = 0;
	if (type == "GrassGround")type_index = 0;
	else if (type == "EarthGround")type_index = 1;
	else if (type == "FieldGround")type_index = 2;
	else if (type == "SnowGround")type_index = 3;
	else if (type == "WaterGround")type_index = 4;

	// Create the ground block
	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	AActor* GroundInstance = nullptr;
	UWorld* World = GetWorld();
	GroundInstance = World->SpawnActor<AActor>(GroundClasses[type_index], SpawnLocation + FVector(x_index * block_size, y_index * block_size, 0.0f), SpawnRotation);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block(x_index, y_index, Cast<AGroundBlockBase>(GroundInstance));

	//Update data system
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(x_index, y_index, type);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(x_index, y_index, 0);
}
void USceneManager::ChangeEarthGroundToSnowGround()
{
	int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
	int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	for (int i = 0; i < x_length; i++)
		for (int j = 0; j < y_length; j++)
		{
			if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_type(i, j) == "EarthGround")
			{
				CreateGroundBlockByLocation(i * block_size, j * block_size, "SnowGround");
			}
		}
}
void USceneManager::ChangeSnowGroundToEarthGround()
{
	int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
	int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	for (int i = 0; i < x_length; i++)
		for (int j = 0; j < y_length; j++)
		{
			if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_type(i, j) == "SnowGround")
			{
				CreateGroundBlockByLocation(i * block_size, j * block_size, "EarthGround");
			}
		}
}
void USceneManager::ChangeEarthGroundToFieldGround(float x, float y)
{
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index;
	int32 y_index;
	GetIndexOfTheGroundBlockByLocation(x, y, x_index, y_index);
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(x_index, y_index) != nullptr)return;
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_type(x_index, y_index) == "EarthGround")
	{
		CreateGroundBlockByLocation(x_index * block_size, y_index * block_size, "FieldGround");
		GetGameInstance()->GetSubsystem<UEventSystem>()->OnEarthGroundPloughed.Broadcast();
	}
}
void USceneManager::ChangeGrassGroundToEarthGround(float x, float y)
{
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index;
	int32 y_index;
	GetIndexOfTheGroundBlockByLocation(x, y, x_index, y_index);
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(x_index, y_index) != nullptr)return;
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_type(x_index, y_index) == "GrassGround")
	{
		CreateGroundBlockByLocation(x_index * block_size, y_index * block_size, "EarthGround");
		GetGameInstance()->GetSubsystem<UEventSystem>()->OnGrassGroundMowed.Broadcast();
	}
}
/*-----------------------------------------------Item Block-----------------------------------------*/
void USceneManager::CreateItemBlockByLocation(float x, float y, int32 id)
{
	if (id == -1)return;
	UClass* item_class = nullptr;

	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	int32 x_index;
	int32 y_index;
	GetIndexOfTheGroundBlockByLocation(x, y, x_index, y_index);

	if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(x_index, y_index) != nullptr)//There is already an item block
	{
		//DestroyItemBlockByLocation(x, y);
		return;
	}

	// Create the item block
	FVector SpawnLocation = FVector(0.0f, 0.0f, kHeight);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	AItemBlockBase* ItemInstance = World->SpawnActor<AItemBlockBase>(AItemBlockBase::StaticClass(), SpawnLocation + FVector(x_index * block_size + block_size / 2, y_index * block_size + block_size / 2, 0), SpawnRotation);
	ItemInstance->InitializeItemBlock(id);

	//Update data system
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_id(x_index, y_index, id);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block(x_index, y_index, ItemInstance);
}
void USceneManager::DestroyItemBlockByLocation(float x, float y)
{
	int32 index_x, index_y;
	try
	{
		GetIndexOfTheGroundBlockByLocation(x, y, index_x, index_y);
	}
	catch (const std::out_of_range& e)
	{
		UE_LOG(LogTemp, Error, TEXT("SceneManager.cpp: DestroyGroundBlockByLocation: %s"), *FString(e.what()));
		return;
	}

	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBlockBase.DT_ItemBlockBase"));
	FStruct_ItemBlockBase* item_info = item_data_table->FindRow<FStruct_ItemBlockBase>(FName(*FString::FromInt(GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_id(index_x, index_y))), "");

	//Update data system
	AItemBlockBase* item_block = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(index_x, index_y);
	if (item_block == nullptr)return;
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_id(index_x, index_y, -1);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_lived_time(index_x, index_y, -1);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_durability(index_x, index_y, -1);
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block(index_x, index_y, nullptr);
	if (item_info != nullptr)
	{
		if (item_info->type_ == 4)//Fire
		{
			for (int32 i = -5; i <= 5; i++)
				for (int32 j = -5; j <= 5; j++)
				{
					if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block(index_x + i, index_y + j) != nullptr)
					{
						int32 new_delta_temperature = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_delta_temperature(index_x + i, index_y + j) - 20;
						GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(index_x + i, index_y + j, new_delta_temperature);
					}
				}
		}
	}

	//Destroy
	bool is_destroyed = item_block->Destroy();
}
void USceneManager::GenerateItems()
{
	int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
	if (GetGameInstance()->GetSubsystem<UDataSystem>()->is_items_initialized())
	{
		UE_LOG(LogTemp, Warning, TEXT("Items are already initialized"));
		for (int i = 0; i < kMaxLength; i++)
			for (int j = 0; j < kMaxLength; j++)
			{
				CreateItemBlockByLocation(i * block_size + block_size / 2, j * block_size + block_size / 2, GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_id(i, j));
			}
	}
	else
	{
		GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(20, 1);//Initial axe
		int32 x_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_x_length();
		int32 y_length = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_y_length();
		for (int i = 1; i <= 25; i++)
			for (int j = 40; j <= 98; j++)
			{
				CreateItemBlockByLocation(i * block_size + block_size / 2, j * block_size + block_size / 2, 2);
			}
		for (int i = 26; i < x_length - 1; i++)
			for (int j = 1; j <= 10; j++)
			{
				int id = rand() % 14 + 1;
				if (id != 5 && id != 6 && id != 12 && id != 13 && id != 14)id = 6;
				CreateItemBlockByLocation(i * block_size + block_size / 2, j * block_size + block_size / 2, id);	
			}
		for (int i = 115; i < x_length - 1; i++)
			for (int j = 11; j <= 43; j++)
			{
				int id = rand() % 14 + 1;
				if (id != 5 && id != 6 && id != 12 && id != 13 && id != 14)id = 6;
				CreateItemBlockByLocation(i * block_size + block_size / 2, j * block_size + block_size / 2, id);
			}
		for (int i = 106; i < x_length - 1; i++)
			for (int j = 44; j < y_length - 1; j++)
			{
				int id = rand() % 14 + 1;
				if (id != 5 && id != 6 && id != 12 && id != 13 && id != 14)id = 6;
				CreateItemBlockByLocation(i * block_size + block_size / 2, j * block_size + block_size / 2, id);
			}
		for (int i = 72; i <= 105; i++)
			for (int j = 114; j < y_length - 1; j++)
			{
				int id = rand() % 14 + 1;
				if (id != 5 && id != 6 && id != 12 && id != 13 && id != 14)id = 6;
				CreateItemBlockByLocation(i * block_size + block_size / 2, j * block_size + block_size / 2, id);
			}
		for (int i = 0; i < x_length; i++)//wall
		{
			CreateItemBlockByLocation(static_cast<float>(i * block_size + block_size / 2), static_cast<float>(block_size / 2), 4);
			CreateItemBlockByLocation(static_cast<float>(i * block_size + block_size / 2), static_cast<float>(y_length * block_size - block_size / 2), 4);
		}
		for (int i = 0; i < y_length; i++)//wall
		{
			CreateItemBlockByLocation(static_cast<float>(block_size / 2), static_cast<float>(i * block_size + block_size / 2), 4);
			CreateItemBlockByLocation(static_cast<float>(x_length * block_size - block_size / 2), static_cast<float>(i * block_size + block_size / 2), 4);
		}
		GetGameInstance()->GetSubsystem<UDataSystem>()->set_is_items_initialized(true);
	}

	/*----------------------------------------------TEST BLOCK------------------------------------------*/
	InvokeUIMenu();
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("WidgetBlueprint'/Game/UMG/WBP_Shortcut.WBP_Shortcut_C'"));
	if (WidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
	/*----------------------------------------------TEST BLOCK------------------------------------------*/
}
UClass* USceneManager::TypeToClass(FString type)//unused.
{
	UClass* item_class = nullptr;
	if (type == "item_block_tree") item_class = LoadObject<UClass>(nullptr, TEXT("/Game/ItemBlock/BP_item_block_tree.BP_item_block_tree_C"));
	else if (type == "item_block_transparent_wall") item_class = LoadObject<UClass>(nullptr, TEXT("/Game/ItemBlock/BP_item_block_transparent_wall.BP_item_block_transparent_wall_C"));
	else if (type == "item_block_crop_wheat") item_class = LoadObject<UClass>(nullptr, TEXT("/Game/ItemBlock/BP_crop/BP_item_block_crop_wheat.BP_item_block_crop_wheat_C"));
	return item_class;
}
void USceneManager::WaterCropAtLocation(float x, float y)
{
	int x_index, y_index;
	GetIndexOfTheGroundBlockByLocation(x, y, x_index, y_index);
	int32 item_id = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_id(x_index, y_index);
	AItemBlockBase* item_class = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(x_index, y_index);

	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBlockBase.DT_ItemBlockBase"));
	FStruct_ItemBlockBase* item_info = item_data_table->FindRow<FStruct_ItemBlockBase>(FName(*FString::FromInt(item_id)), "");

	if (item_info == nullptr)return;
	if (item_info->type_ == 1)//crop
	{
		//UE_LOG(LogTemp, Warning, TEXT("Watering Crop %d, %d"), x_index, y_index);
		item_class->WaterThisCrop();
	}
}
void USceneManager::ItemBlockInteractionHandler(int32 interaction_type, int32 damage, float x, float y)
{
	int x_index, y_index;
	GetIndexOfTheGroundBlockByLocation(x, y, x_index, y_index);
	int32 item_id = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_id(x_index, y_index);
	
	if (item_id == -1)return;
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBlockBase.DT_ItemBlockBase"));
	FStruct_ItemBlockBase* item_info = item_data_table->FindRow<FStruct_ItemBlockBase>(FName(*FString::FromInt(item_id)), "");
	if (item_info == nullptr)return;
	else
	{
		if (item_info->interaction_accepted_.Find(interaction_type) != INDEX_NONE)//interaction accepted
		{
			if (interaction_type == 5 || interaction_type == 8)
			{
				int32 previous_durability = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_durability(x_index, y_index);
				GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_durability(x_index, y_index, previous_durability - damage);
				//UE_LOG(LogTemp, Warning, TEXT("Durability: %d"), previous_durability - damage);
				if (previous_durability - damage <= 0)
				{
					for (auto item : item_info->map_item_drop_)
					{
						GetGameInstance()->GetSubsystem<UEventSystem>()->OnGivenItems.Broadcast(item.Key, item.Value);
					}
					DestroyItemBlockByLocation(x, y);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Interaction not accepted"));
		}
	}
}

void USceneManager::InvokeUIMenu()
{
	if (is_menu_exist)
	{
		return;
	}
	else is_menu_exist = true;
	GetGameInstance()->GetFirstLocalPlayerController()->SetPause(true);
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/UMG/WBP_Menu.WBP_Menu_C"));
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	if (WidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetGameInstance(), WidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}

void USceneManager::SetIsMenuExistToFalse()
{
	is_menu_exist = false;
}
