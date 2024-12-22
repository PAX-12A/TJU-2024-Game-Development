// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine\DataTable.h"
#include "Struct_ItemBase.h"
#include "DataSystem.h"
#include "MyCharacter.h"
#include "ItemButton.h"
#include "Marketmanager.generated.h"

/**
 * 
 */
USTRUCT()
struct Fitem {
	GENERATED_USTRUCT_BODY()
	FString name;
	int32 price;
};
UCLASS()
class STARDEWVALLEY_API UMarketmanager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// 当前物品
	Fitem it;

	// 物品数据表，加载并存储物品数据
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));

	// 获取物品信息
	void getInfo(int32 id) {
		// 使用 ID 查找物品，确保查找成功
		if (item_data_table) {
			FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(id)), "");
			if (item_info) {
				// 如果找到了物品数据，填充当前物品
				it.name = item_info->name_;
				it.price = item_info->price_;
				UE_LOG(LogTemp, Log, TEXT("Item found: %s, Price: %d"), *it.name, it.price);
			}
			else {
				// 如果没有找到物品数据
				UE_LOG(LogTemp, Error, TEXT("Item with ID %d not found in data table."), id);
			}
		}
		else {
			// 如果数据表为空，提示加载失败
			UE_LOG(LogTemp, Error, TEXT("Item data table not loaded properly."));
		}
	}

	// 销售物品
	void Sell() {
		UDataSystem* dataSystem = GetGameInstance()->GetSubsystem<UDataSystem>();
		if (dataSystem) {
			// 增加金币
			dataSystem->coin += it.price;

			// 日志记录
			UE_LOG(LogTemp, Warning, TEXT("YOU SOLD AN ITEM! Item: %s, Price: %d"), *it.name, it.price);
			UE_LOG(LogTemp, Warning, TEXT("New coin balance: %d"), dataSystem->coin);
		}
		else {
			// 如果数据系统为空，记录错误
			UE_LOG(LogTemp, Error, TEXT("DataSystem subsystem is not available."));
		}
	}

	// 购买物品
	void Buy() {
		UDataSystem* dataSystem = GetGameInstance()->GetSubsystem<UDataSystem>();
		if (dataSystem) {
			// 检查是否有足够的金币来购买物品
			if (dataSystem->coin >= it.price) {
				// 扣除金币
				dataSystem->coin -= it.price;

				UE_LOG(LogTemp, Warning, TEXT("YOU BOUGHT AN ITEM! Item: %s, Price: %d"), *it.name, it.price);
				UE_LOG(LogTemp, Warning, TEXT("New coin balance: %d"), dataSystem->coin);
			}
			else {
				// 如果金币不足，记录错误
				UE_LOG(LogTemp, Error, TEXT("Not enough coins to buy item: %s, Price: %d. Current balance: %d"), *it.name, it.price, dataSystem->coin);
			}
		}
		else {
			// 如果数据系统为空，记录错误
			UE_LOG(LogTemp, Error, TEXT("DataSystem subsystem is not available."));
		}
	}
	void Initialize(FSubsystemCollectionBase& Collection);
};