// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************************
 * \file   MyCharacter.cpp
 * \brief  The Description of the character class
 *
 * \author magician
 * \date   December 2024
 *********************************************************************/

#include "MyCharacter.h"

#include "GameFramework\SpringArmComponent.h"
#include "Camera\CameraComponent.h"
#include "Components\InputComponent.h"
#include "Components\StaticMeshComponent.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create SpringArm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	//Attach SpringArm
	SpringArmComponent->SetupAttachment(RootComponent);
	//Set SpringArm Rotation
	SpringArmComponent->SetWorldRotation(FRotator(-80.f, 0.f, 0.f));
	//Set SpringArm Length
	SpringArmComponent->TargetArmLength = 600.f;

	//Set Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	//Attach Camera
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Bind MoveY Function
	PlayerInputComponent->BindAxis(FName("MoveY"), this, &AMyCharacter::MoveY);
	//Bind MoveX Function
	PlayerInputComponent->BindAxis(FName("MoveX"), this, &AMyCharacter::MoveX);
	//Bind MoveUp Function
	PlayerInputComponent->BindAxis(FName("MoveUp"), this, &AMyCharacter::MoveUp);
}

void AMyCharacter::MoveY(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::MoveX(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::MoveUp(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveUp"));
	SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, Value)); //Move UpLocation
	//AddMovementInput(GetActorUpVector(), Value);
}