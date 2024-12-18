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

	UE_LOG(LogTemp, Warning, TEXT("Set MyCharacter To Player0"));

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

	// Set Auto Possess Player to Player 0
	//this->AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	//Bind Equipment Functions
	PlayerInputComponent->BindAction(FName("Equip1"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool1);
	PlayerInputComponent->BindAction(FName("Equip2"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool2);
	PlayerInputComponent->BindAction(FName("Equip3"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool3);
	PlayerInputComponent->BindAction(FName("Equip4"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool4);
	PlayerInputComponent->BindAction(FName("Equip5"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool5);
	PlayerInputComponent->BindAction(FName("Equip6"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool6);
	PlayerInputComponent->BindAction(FName("Equip7"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool7);
	PlayerInputComponent->BindAction(FName("Equip8"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool8);
	PlayerInputComponent->BindAction(FName("Equip9"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool9);
	PlayerInputComponent->BindAction(FName("Equip10"), IE_Pressed, this, &AMyCharacter::CharacterEquipTool10);

	//Bind Skill Functions
	PlayerInputComponent->BindAction(FName("Skill1"), IE_Pressed, this, &AMyCharacter::UseSkill1);
	PlayerInputComponent->BindAction(FName("Skill2"), IE_Pressed, this, &AMyCharacter::UseSkill2);
	PlayerInputComponent->BindAction(FName("Skill3"), IE_Pressed, this, &AMyCharacter::UseSkill3);
	PlayerInputComponent->BindAction(FName("Skill4"), IE_Pressed, this, &AMyCharacter::UseSkill4);

	//Call the Menu
	PlayerInputComponent->BindAction(FName("Menu"), IE_Pressed, this, &AMyCharacter::CallMenu);
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

void AMyCharacter::CharacterEquipTool1() {
	now_tool = 1;
}
void AMyCharacter::CharacterEquipTool2() {
	now_tool = 2;
}
void AMyCharacter::CharacterEquipTool3() {
	now_tool = 3;
}
void AMyCharacter::CharacterEquipTool4() {
	now_tool = 4;
}
void AMyCharacter::CharacterEquipTool5() {
	now_tool = 5;
}
void AMyCharacter::CharacterEquipTool6() {
	now_tool = 6;
}
void AMyCharacter::CharacterEquipTool7() {
	now_tool = 7;
}
void AMyCharacter::CharacterEquipTool8() {
	now_tool = 8;
}
void AMyCharacter::CharacterEquipTool9() {
	now_tool = 9;
}
void AMyCharacter::CharacterEquipTool10() {
	now_tool = 10;
}

void AMyCharacter::CharacterToolsUse() {

}

//kan fa
void AMyCharacter::UseSkill1() {

}
//kai cai
void AMyCharacter::UseSkill2() {

}
//chu di
void AMyCharacter::UseSkill3() {

}
//ge cao
void AMyCharacter::UseSkill4() {

}

void AMyCharacter::CallMenu() {
	UE_LOG(LogTemp, Warning, TEXT("Call Menu"));
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnCallingMenu.Broadcast();
}
/*
void AMyCharacter::SkillLevelUpdate(int32 skill_experience, int32 skill_type) {
	for (int32 i = skill_level[skill_type]; i <= 19; i++) {
		if (skill_experience >= experience_table[i]) {
			skill_level[skill_type]++;
			skill_experience -= experience_table[i];
		}
	}
}
*/

void AMyCharacter::CharacterLocationUpdate() {
	CharacterLocation = this->GetActorLocation();
}