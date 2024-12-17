// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************************
 * \file   MyCharacter.h
 * \brief  The Definition of the character class
 *
 * \author magician
 * \date   December 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EventSystem.h"
#include "MyCharacter.generated.h"

UCLASS()
class STARDEWVALLEY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

private:
	//Move in Y direction
	void MoveY(float Value);

	//Move in X direction
	void MoveX(float Value);

	//Move in Up direction
	void MoveUp(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
