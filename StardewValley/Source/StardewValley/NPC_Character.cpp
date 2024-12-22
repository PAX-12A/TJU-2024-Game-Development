// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Character.h"

// Sets default values
ANPC_Character::ANPC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC_Character::BeginPlay()
{
	Super::BeginPlay();
	WalkTurnDirectionDelegate.BindUObject(this, &ANPC_Character::SetMoveDirection);
	GetGameInstance()->GetWorld()->GetTimerManager().SetTimer(WalkTimerHandle, WalkTurnDirectionDelegate, 3.0f, true);
}

// Called every frame
void ANPC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsTimeToWalkForward) {
		MoveForward();
	}
	else {
		MoveBackward();
	}
}

// Called to bind functionality to input
void ANPC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC_Character::MoveForward()
{
	SetActorLocation(GetActorLocation() + FVector(0.f, 3.f, 0.f));
	SetActorLocation(GetActorLocation() + FVector(3.f, 0.f, 0.f));
}

void ANPC_Character::MoveBackward()
{
	SetActorLocation(GetActorLocation() + FVector(0.f, -3.f, 0.f));
	SetActorLocation(GetActorLocation() + FVector(-3.f, 0.f, 0.f));
}

void ANPC_Character::SetMoveDirection() {
	bIsTimeToWalkForward = !bIsTimeToWalkForward;
}