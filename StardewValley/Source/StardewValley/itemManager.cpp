// Fill out your copyright notice in the Description page of Project Settings.


#include "itemManager.h"
#include "EventSystem.h"
#include "myItem.h"
#include"DataSystem.h"
#include"Struct_ItemBase.h"
UitemManager::UitemManager()
{
	shortBar.Init(-1, shortBarSize+1);
	//GetGameInstance()->GetSubsystem<UDataSystem>()->set_shortBar(shortBar);

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
	EventSystem->OnItemBlockAttacked.AddUObject(this, &UitemManager::useTool);



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

void UitemManager::useTool(int32 interractionType,int32 damage,float x,float y)
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

	const int iron = 9;
	const int cropper = 8;
	const int wood = 18;
	const int coal = 7;

	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));
	FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(itemId)), "");
	



	if (item_info != nullptr)
	{
		UTexture2D* texture = item_info->icon_;
		TMap<int32, int32> Table = item_info->makeTable;										
		for (auto& i : Table)
		{
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnGivenItems.Broadcast(i.Key, -(i.Value));						
		}
		GetGameInstance()->GetSubsystem<UEventSystem>()->OnGivenItems.Broadcast(itemId, 1);
		
		
		
	}


}

void UitemManager::deleteItem(int itemId,int index)//shoule except some parameter and broadcast
{
	shortBar[index] = 0;
	GetGameInstance()->GetSubsystem<UDataSystem>()->set_shortBar(shortBar);//set data in data system
}


