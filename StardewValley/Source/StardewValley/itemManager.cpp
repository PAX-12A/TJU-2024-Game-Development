// Fill out your copyright notice in the Description page of Project Settings.


#include "itemManager.h"
#include "EventSystem.h"
#include "myItem.h"
#include"DataSystem.h"

UitemManager::UitemManager()
{
	shortBar.Init(0, shortBarSize);

	//the table of some item
	AxeComposeTable.Add(9, 3);//iron 3
	AxeComposeTable.Add(18, 3);//wood 3

	HoeComposeTable.Add(9, 2);//iron 2
	HoeComposeTable.Add(18, 2);//wood 2

	ScytheComposeTable.Add(9, 2);//iron 2
	ScytheComposeTable.Add(18, 3);//wood 3

	PickComposeTable.Add(9, 3);//iron 3
	PickComposeTable.Add(18, 2);//wood 2
}


void UitemManager::Initialize(FSubsystemCollectionBase& Collection)
{

	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("CharacterManager Initialize"));

	UEventSystem* EventSystem = Collection.InitializeDependency<UEventSystem>();

	
	
	EventSystem->OnItemAddedToShortcutBar.AddUObject(this, &UitemManager::putItemShortBar);
	EventSystem->OnItemRemovedFromShortcutBar.AddUObject(this, &UitemManager::removeItemShortBar);
	EventSystem->OnToolUsed.AddUObject(this, &UitemManager::useTool);



}




void UitemManager::itemGenerate()
{
	UE_LOG(LogTemp, Warning, TEXT("item Generate"));
	UClass* AmyItemClass = LoadObject<UClass>(nullptr, TEXT("/Game/Item/BP_item.BP_item_C"));


	UWorld* World = GetWorld();
	AmyItem* itemInstance = World->SpawnActor<AmyItem>(AmyItemClass);//generate item
}





void UitemManager::putItemShortBar(int32 receiveId,int32 receiveIndex)
{
	
	shortBar[receiveIndex] = receiveId;
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_shortBar(shortBar);
	
}

void UitemManager::removeItemShortBar(int32 removeIndex)
{
	shortBar[removeIndex] = 0;
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_shortBar(shortBar);//set data in data system
}

void UitemManager::useTool(int32 useIndex)
{
	




}

int32 UitemManager::chooseItem(int index)//receive broadcast
{
	return shortBar[index];
}

void UitemManager::makeItem(int itemId)//shoule except some parameter and broadcast
{	
	TMap<int32, int32> playerBag;
	playerBag=GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_bag();

	if (itemId == 20)
	{
		if(playerBag[9]>=3&&playerBag[18]>=3)
		{
			playerBag[9] -= 3;
			playerBag[18] -= 3;
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(9,-3);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(18,-3);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(20, 1);
		}
	}
	else if (itemId == 21)
	{
		if (playerBag[9] >= 2 && playerBag[18] >= 2)
		{
			playerBag[9] -= 2;
			playerBag[18] -= 2;
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(9, -2);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(18, -2);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(21, 1);
		}
	}
	else if (itemId == 22)
	{
		if (playerBag[9] >= 2 && playerBag[18] >= 3)
		{
			playerBag[9] -= 2;
			playerBag[18] -= 3;
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(9, -2);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(18, -3);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(22, 1);
		}
	}
	else if (itemId == 23)
	{
		if (playerBag[9] >= 3 && playerBag[18] >= 2)
		{
			playerBag[9] -= 3;
			playerBag[18] -= 2;
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(9, -3);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(18, -2);
			GetGameInstance()->GetSubsystem<UDataSystem>()->add_item_to_bag(23, 1);
		}
	}
}

void UDataSystem::Deinitialize()
{
	Super::Deinitialize();

	SaveGame();
}