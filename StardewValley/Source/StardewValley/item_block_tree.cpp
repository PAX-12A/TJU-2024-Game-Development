// Fill out your copyright notice in the Description page of Project Settings.


#include "item_block_tree.h"
#include "Components/StaticMeshComponent.h"

Aitem_block_tree::Aitem_block_tree()
{
	PrimaryActorTick.bCanEverTick = true;

	foliage_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("foliage"));
	foliage_mesh_->SetupAttachment(RootComponent);
}