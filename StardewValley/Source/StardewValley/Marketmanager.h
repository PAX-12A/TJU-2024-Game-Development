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
	// ��ǰ��Ʒ
	Fitem it;

	// ��Ʒ���ݱ����ز��洢��Ʒ����
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));

	// ��ȡ��Ʒ��Ϣ
	void getInfo(int32 id) {
		// ʹ�� ID ������Ʒ��ȷ�����ҳɹ�
		if (item_data_table) {
			FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(id)), "");
			if (item_info) {
				// ����ҵ�����Ʒ���ݣ���䵱ǰ��Ʒ
				it.name = item_info->name_;
				it.price = item_info->price_;
				UE_LOG(LogTemp, Log, TEXT("Item found: %s, Price: %d"), *it.name, it.price);
			}
			else {
				// ���û���ҵ���Ʒ����
				UE_LOG(LogTemp, Error, TEXT("Item with ID %d not found in data table."), id);
			}
		}
		else {
			// ������ݱ�Ϊ�գ���ʾ����ʧ��
			UE_LOG(LogTemp, Error, TEXT("Item data table not loaded properly."));
		}
	}

	// ������Ʒ
	void Sell() {
		UDataSystem* dataSystem = GetGameInstance()->GetSubsystem<UDataSystem>();
		if (dataSystem) {
			// ���ӽ��
			dataSystem->coin += it.price;

			// ��־��¼
			UE_LOG(LogTemp, Warning, TEXT("YOU SOLD AN ITEM! Item: %s, Price: %d"), *it.name, it.price);
			UE_LOG(LogTemp, Warning, TEXT("New coin balance: %d"), dataSystem->coin);
		}
		else {
			// �������ϵͳΪ�գ���¼����
			UE_LOG(LogTemp, Error, TEXT("DataSystem subsystem is not available."));
		}
	}

	// ������Ʒ
	void Buy() {
		UDataSystem* dataSystem = GetGameInstance()->GetSubsystem<UDataSystem>();
		if (dataSystem) {
			// ����Ƿ����㹻�Ľ����������Ʒ
			if (dataSystem->coin >= it.price) {
				// �۳����
				dataSystem->coin -= it.price;

				UE_LOG(LogTemp, Warning, TEXT("YOU BOUGHT AN ITEM! Item: %s, Price: %d"), *it.name, it.price);
				UE_LOG(LogTemp, Warning, TEXT("New coin balance: %d"), dataSystem->coin);
			}
			else {
				// �����Ҳ��㣬��¼����
				UE_LOG(LogTemp, Error, TEXT("Not enough coins to buy item: %s, Price: %d. Current balance: %d"), *it.name, it.price, dataSystem->coin);
			}
		}
		else {
			// �������ϵͳΪ�գ���¼����
			UE_LOG(LogTemp, Error, TEXT("DataSystem subsystem is not available."));
		}
	}
	void Initialize(FSubsystemCollectionBase& Collection);
};