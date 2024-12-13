// Fill out your copyright notice in the Description page of Project Settings.


#include "ShortcutBar.h"
#include "Engine/DataTable.h"
#include "Struct_ItemBase.h"
#include "Components/Image.h"
#include "EventSystem.h"

bool UShortcutBar::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	auto GameInstance = GetGameInstance();
	if (GameInstance != nullptr)
	{
		auto EventSystem = GameInstance->GetSubsystem<UEventSystem>();
		if (EventSystem != nullptr)
		{
			EventSystem->OnItemAddedToShortcutBar.AddUObject(this, &UShortcutBar::AddItemToShortcutBar);
			EventSystem->OnItemRemovedFromShortcutBar.AddUObject(this, &UShortcutBar::RemoveItemFromShortcutBar);
		}
	}
	return true;
}

void UShortcutBar::AddItemToShortcutBar(int32 id, int32 index)
{
	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));
	FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(id)), "");
	FName name = FName("IcoItem_" + FString::FromInt(index));
	UE_LOG(LogTemp, Warning, TEXT("name = %s"), *name.ToString());
	UImage* image = Cast<UImage>(GetWidgetFromName(name));

	UE_LOG(LogTemp, Warning, TEXT("id = %d, index = %d, image = %p, item_info = %p"), id, index, image, item_info);

	if (image != nullptr && item_info != nullptr)
	{
		UTexture2D* texture = item_info->icon_;
		FSlateBrush brush;
		brush.SetResourceObject(texture);
		image->SetBrush(brush);
		image->SetRenderScale(FVector2D(3.0f, 3.0f));
	}
	else
	{
		UTexture2D* texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Asset/Icon/Ico_Test_4oD.Ico_Test_4oD'"));
		FSlateBrush brush;
		brush.SetResourceObject(texture);
		image->SetBrush(brush);
		image->SetRenderScale(FVector2D(3.0f, 3.0f));
	}
}

void UShortcutBar::RemoveItemFromShortcutBar(int32 index)
{
	FName name = FName("IcoItem_" + FString::FromInt(index));
	UImage* image = Cast<UImage>(GetWidgetFromName(name));
	if (image != nullptr)
	{
		UTexture2D* texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Asset/Icon/Ico_Axe_Level1.Ico_Axe_Level1'"));
		FSlateBrush brush;
		brush.SetResourceObject(texture);
		image->SetBrush(brush);
		image->SetRenderScale(FVector2D(3.0f, 3.0f));
	}
}
