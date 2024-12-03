// Fill out your copyright notice in the Description page of Project Settings.


#include "item_block_transparent_wall.h"
#include "Components/BoxComponent.h"

Aitem_block_transparent_wall::Aitem_block_transparent_wall()
{
	PrimaryActorTick.bCanEverTick = true;

	wall_ = CreateDefaultSubobject<UBoxComponent>(TEXT("wall_"));
	wall_->SetBoxExtent(FVector(20, 20, 100));
	wall_->SetCollisionObjectType(ECC_WorldStatic);
	wall_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	wall_->SetupAttachment(RootComponent);
}