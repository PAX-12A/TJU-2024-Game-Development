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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		//Show Mouse
		PlayerController->bShowMouseCursor = true;

		//permit click
		PlayerController->bEnableClickEvents = true;

		//Permit Mouse Over
		PlayerController->bEnableMouseOverEvents = true;

		//Unlock Mouse
		PlayerController->SetInputMode(FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock));
	}
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

	//Call the Menu
	PlayerInputComponent->BindAction(FName("Menu"), IE_Pressed, this, &AMyCharacter::CallMenu);
}

void AMyCharacter::MoveY(float Value)
{
	AddMovementInput(GetActorForwardVector(), 1.5 * Value);
}

void AMyCharacter::MoveX(float Value)
{
	AddMovementInput(GetActorRightVector(), 1.5 * Value);
}

void AMyCharacter::MoveUp(float Value)
{
	SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, Value)); //Move UpLocation
}

void AMyCharacter::CharacterEquipTool1() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool1"));
	now_tool_ = 1;
}
void AMyCharacter::CharacterEquipTool2() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool2"));
	now_tool_ = 2;
}
void AMyCharacter::CharacterEquipTool3() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool3"));
	now_tool_ = 3;
}
void AMyCharacter::CharacterEquipTool4() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool4"));
	now_tool_ = 4;
}
void AMyCharacter::CharacterEquipTool5() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool5"));
	now_tool_ = 5;
}
void AMyCharacter::CharacterEquipTool6() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool6"));
	now_tool_ = 6;
}
void AMyCharacter::CharacterEquipTool7() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool7"));
	now_tool_ = 7;
}
void AMyCharacter::CharacterEquipTool8() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool8"));
	now_tool_ = 8;
}
void AMyCharacter::CharacterEquipTool9() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool9"));
	now_tool_ = 9;
}
void AMyCharacter::CharacterEquipTool10() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool10"));
	now_tool_ = 10;
}

void AMyCharacter::CharacterToolsUse() {
	UE_LOG(LogTemp, Warning, TEXT("CharacterUseTools"));
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnToolUsed.Broadcast(now_tool_);

}

//Cut Down Object(Use axe)
void AMyCharacter::UseSkill1() {
	if (bIsAxeCoolDown) {
		UE_LOG(LogTemp, Warning, TEXT("Skill1 is not cooling down"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UsingSkill1"));
	int32 axe_level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_axe_level();
	bIsAxeCoolDown = true;
	axe_range_ = axe_level * 50.f + default_axe_range_;
	GetWorldTimerManager().SetTimer(AxeTimerHandle, this, &AMyCharacter::AxeEndCoolDown, axe_cool_down_duration);
}
//Hoe Ground(Use hoe)
void AMyCharacter::UseSkill2() {
	if (bIsHoeCoolDown) {
		UE_LOG(LogTemp, Warning, TEXT("Skill2 is not cooling down"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UsingSkill2"));
	int32 hoe_level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_hoe_level();
	bIsHoeCoolDown = true;
	hoe_range_ = hoe_level * 50.f + default_hoe_range_;
	GetWorldTimerManager().SetTimer(HoeTimerHandle, this, &AMyCharacter::HoeEndCoolDown, hoe_cool_down_duration);
}

//Mow(Use scythe)
void AMyCharacter::UseSkill3() {
	if (bIsScytheCoolDown) {
		UE_LOG(LogTemp, Warning, TEXT("Skill3 is not cooling down"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UsingSkill3"));
	int32 scythe_level = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_scythe_level();
	bIsScytheCoolDown = true;
	scythe_range_ = scythe_level * 50.f + default_scythe_range_;
	GetWorldTimerManager().SetTimer(ScytheTimerHandle, this, &AMyCharacter::ScytheEndCoolDown, scythe_cool_down_duration);
}

void AMyCharacter::AxeEndCoolDown() {
	bIsAxeCoolDown = false;
	axe_range_ = default_axe_range_;
	GetWorldTimerManager().ClearTimer(AxeTimerHandle);
}

void AMyCharacter::HoeEndCoolDown() {
	bIsHoeCoolDown = false;
	hoe_range_ = default_hoe_range_;
	GetWorldTimerManager().ClearTimer(HoeTimerHandle);
}

void AMyCharacter::ScytheEndCoolDown() {
	bIsScytheCoolDown = false;
	scythe_range_ = default_scythe_range_;
	GetWorldTimerManager().ClearTimer(ScytheTimerHandle);
}

void AMyCharacter::CallMenu() {
	UE_LOG(LogTemp, Warning, TEXT("Call Menu"));
	CharacterLocationUpdate();
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnCallingMenu.Broadcast();
}

void AMyCharacter::CharacterLocationUpdate() {
	CharacterLocation = this->GetActorLocation();
}