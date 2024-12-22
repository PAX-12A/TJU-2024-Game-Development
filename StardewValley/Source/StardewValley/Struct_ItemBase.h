// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Struct_ItemBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStruct_ItemBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FStruct_ItemBase() 
		: id_(0)
		, icon_(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 id_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	UTexture2D* icon_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 interaction_type_;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	FString name_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 attack_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 price_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 max_durability_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 durability_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	float use_area;//fanwei

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	int32 putId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Your Category")
	TMap<int32, int32> makeTable;

	//背包到快捷栏输出一个数组到数据系统


};
