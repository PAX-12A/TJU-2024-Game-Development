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

void USceneManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    TypeToSizeMap.Add("item_block_tree", { 2, 2 });

    UWorld* World = GetWorld();
    if (World)
    {
        World->GetTimerManager().SetTimer(timer_handler_, this, &USceneManager::GenerateMap, 2.0f, false);//Delay the generation of the map, otherwise the world may not be ready, and the map will not be generated
    }
    GetGameInstance()->GetSubsystem<UEventSystem>()->OnGroundGenerated.AddUObject(this, &USceneManager::GenerateItems);
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
        if (x_length == 0 || y_length == 0 || block_size == 0)
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

            for (int i = 100; i < x_length; i++)
            {
                for (int j = 29; j < y_length; j++)
                {
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, j, "WaterGround");
                }
            }
            for (int i = 0; i < 28; i++)
			{
				for (int j = 30; j < 70; j++)
				{
					GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i, j, "EarthGround");
                    GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(i + 50, y_length - 1 - j, "EarthGround");
				}
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
            if(GetGameInstance()->GetSubsystem<UEventSystem>()->OnGroundGenerated.IsBound())
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
    int32 base_temperature = GetGameInstance()->GetSubsystem<UDataSystem>()->get_present_base_temprature();
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

    if (x < 0 || y < 0  || x_index >= x_length || y_index >= y_length)
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
    catch(const std::out_of_range& e)
	{

		UE_LOG(LogTemp, Error, TEXT("SceneManager.cpp: DestroyGroundBlockByLocation: %s"), *FString(e.what()));
		return;
	}
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_type(index_x, index_y, "");
    GetGameInstance()->GetSubsystem<UDataSystem>()->set_ground_block_delta_temperature(index_x, index_y, 0);
    if(GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block(index_x, index_y) == nullptr)return;
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

void USceneManager::CreateItemBlockByLocation(float x, float y, FString type)
{
    UClass* item_class = nullptr;
    item_class = TypeToClass(type);
    if (item_class == nullptr)
    {
        return;
    }

    int32 block_size = GetGameInstance()->GetSubsystem<UDataSystem>()->get_ground_block_size();
    int32 x_index = static_cast<int32>(x / block_size);
    int32 y_index = static_cast<int32>(y / block_size);
    int32 x_length = kMaxLength;
    int32 y_length = kMaxLength;

    if (x < 0 || y < 0 || x_index + TypeToSizeMap[type].x_length - 1 >= x_length || y_index + TypeToSizeMap[type].y_length - 1 >= y_length)
    {
		throw std::out_of_range("Out of range");
    }
    
    if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(x_index, y_index) != nullptr)//There is already an item block
	{
		//DestroyItemBlockByLocation(x, y);
        return;
	}

	// Create the item block
	FVector SpawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	AActor* ItemInstance = nullptr;
	UWorld* World = GetWorld();
    if (World == nullptr) return;
    item_class = LoadObject<UClass>(nullptr, TEXT("/Game/ItemBlock/BP_item_block_tree.BP_item_block_tree_C"));
	ItemInstance = World->SpawnActor<AActor>(item_class, SpawnLocation + FVector(x_index * block_size, y_index * block_size, 0.0f), SpawnRotation);

    //Update data system
	for (int i = x_index; i < x_index + TypeToSizeMap[type].x_length; i++)
        for (int j = y_index; j < y_index + TypeToSizeMap[type].y_length; j++)
        {
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_type(i, j, type);
			GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block(i, j, Cast<AItemBlockBase>(ItemInstance));
        }
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

    //Update data system
    AItemBlockBase* item_block = GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(index_x, index_y);
    if (item_block == nullptr)return;
    for (int i = 0; i < kMaxLength; i++)
        for (int j = 0; j < kMaxLength; j++)
		{
			if (GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block(i, j) == item_block)
			{ 
                GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block_type(i, j, "");
				GetGameInstance()->GetSubsystem<UDataSystem>()->set_item_block(i, j, nullptr);
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
        for (int i =0; i < kMaxLength; i++)
            for (int j = 0; j < kMaxLength; j++)
            {
                CreateItemBlockByLocation(i * block_size, j * block_size, GetGameInstance()->GetSubsystem<UDataSystem>()->get_item_block_type(i, j));
            }
    }
    else
    {
        for (int i = 55; i < 60; i++)
            for (int j = 55; j < 60; j++)
            {
                CreateItemBlockByLocation(i * block_size, j * block_size, "item_block_tree");
            }
        GetGameInstance()->GetSubsystem<UDataSystem>()->set_is_items_initialized(true);
    }
    //DestroyItemBlockByLocation(55 * block_size, 55 * block_size);
}
UClass* USceneManager::TypeToClass(FString type)
{
	UClass* item_class = nullptr;
	if (type == "item_block_tree") item_class = LoadObject<UClass>(nullptr, TEXT("/Game/ItemBlock/BP_item_block_tree.BP_item_block_tree_C"));
	return item_class;
}
