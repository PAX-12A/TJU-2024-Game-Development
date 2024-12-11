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
};
