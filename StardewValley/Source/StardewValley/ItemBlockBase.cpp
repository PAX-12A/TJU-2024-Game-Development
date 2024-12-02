// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBlockBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AItemBlockBase::AItemBlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	item_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("item_mesh_"));
	RootComponent = item_mesh_;
}

// Called when the game starts or when spawned
void AItemBlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

