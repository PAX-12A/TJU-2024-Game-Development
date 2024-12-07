/*****************************************************************//**
 * \file   GroundBlockBase.cpp
 * \brief  The implementation of the ground block base
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/

#include "GroundBlockBase.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGroundBlockBase::AGroundBlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ground_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ground_mesh_"));
	RootComponent = ground_mesh_;
}

// Called when the game starts or when spawned
void AGroundBlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroundBlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

