// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Character.generated.h"

UCLASS()
class STARDEWVALLEY_API ANPC_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerDelegate WalkTurnDirectionDelegate;
	FTimerHandle WalkTimerHandle;
	float WalkTime = 3.0f;
	bool bIsTimeToWalkForward = true;
	void MoveForward();
	void MoveBackward();
	void SetMoveDirection();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
