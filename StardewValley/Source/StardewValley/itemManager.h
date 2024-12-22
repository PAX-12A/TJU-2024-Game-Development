// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "itemManager.generated.h"

/**
 * 
 */
UCLASS()
class STARDEWVALLEY_API UitemManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
protected:


	TMap<int32,int32> AxeComposeTable;
	TMap<int32,int32> HoeComposeTable;
	TMap<int32,int32> ScytheComposeTable;
	TMap<int32,int32> PickComposeTable;




	static const int32 shortBarSize = 10;
	TArray<int32> shortBar;
	


public:
	UitemManager();
	
	void Initialize(FSubsystemCollectionBase& Collection);

	void itemGenerate();

	void putItemShortBar(int32 receiveId, int32 receiveIndex);

	void removeItemShortBar(int32 removeIndex);

	void useTool(int32 interractionType, int32 damage, float x, float y);

	int32 chooseItem(int index);

	void makeItem(int itemId);

	void deleteItem(int itemId,int index);


	

};
