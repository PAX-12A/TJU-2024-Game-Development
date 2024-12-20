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

	//Bind Mouse Click
	PlayerInputComponent->BindAction(FName("Click"), IE_Pressed, this, &AMyCharacter::MouseClick);

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
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool2() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool2"));
	now_tool_ = 2;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool3() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool3"));
	now_tool_ = 3;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool4() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool4"));
	now_tool_ = 4;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool5() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool5"));
	now_tool_ = 5;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool6() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool6"));
	now_tool_ = 6;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool7() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool7"));
	now_tool_ = 7;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool8() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool8"));
	now_tool_ = 8;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool9() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool9"));
	now_tool_ = 9;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}
void AMyCharacter::CharacterEquipTool10() {
	UE_LOG(LogTemp, Warning, TEXT("Equip Tool10"));
	now_tool_ = 10;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEquipTool.Broadcast(now_tool_);
}

void AMyCharacter::MouseClick() {
	UE_LOG(LogTemp, Warning, TEXT("Mouse Click"));
	CharacterLocationUpdate();
	UE_LOG(LogTemp, Warning, TEXT("Character Location: %f, %f, %f"), CharacterLocation.X, CharacterLocation.Y, CharacterLocation.Z);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FVector HitLocation;
		FVector HitNormal;
		FHitResult Hit;
		if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			HitLocation = Hit.Location;
			//Use Tools
			CharacterToolsUse(HitLocation);
		}
	}
}

void AMyCharacter::CharacterToolsUse(FVector Location) {
	UE_LOG(LogTemp, Warning, TEXT("Hit Location: %f, %f, %f"), Location.X, Location.Y, Location.Z);
	UE_LOG(LogTemp, Warning, TEXT("CharacterUseTools"));

	int32 now_tool_id = now_tool_;//now_tool_id is the exact type of the tool
	//now_tool_ = GetGameInstance()->GetSubsystem<UDataSystem>()->get_tools_id(now_tool_);
	float now_tool_range = 200.0f;
	//now_tool_range = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_tool_range(now_tool_);
	float skill_add_range = 100.0f;
	//skill_add_range = GetGameInstance()->GetSubsystem<UDataSystem>()->get_player_skill_add_range(now_tool_);
	float permit_range = now_tool_range + skill_add_range;
	float distance = sqrt(pow(Location.X - CharacterLocation.X, 2) + pow(Location.Y - CharacterLocation.Y, 2));
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);
	if (fabs(permit_range - distance) > KINDA_SMALL_NUMBER) {
		//if (now_tool_id == 1)//tool is scythe
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnMowingGrassGround.Broadcast(Location.X, Location.Y);
		//if (now_tool_id == 2)//tool is hoe
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnPloughingEarthGround.Broadcast(Location.X, Location.Y);
		//else
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnToolsTowardsItemBlock.Broadcast(now_tool_id, Location.X, Location.Y);
	}
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