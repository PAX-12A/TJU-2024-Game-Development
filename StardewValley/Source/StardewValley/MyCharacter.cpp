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
	SpringArmComponent->SetWorldRotation(FRotator(-45.f, 0.f, 0.f));
	//Set SpringArm Length
	SpringArmComponent->TargetArmLength = 600.f;

	//Set Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	//Attach Camera
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Set Auto Possess Player to Player 0
	//this->AutoPossessPlayer = EAutoReceiveInput::Player0;
	Player_Money = 100;
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

	//GetGameInstance()->GetSubsystem<UEventSystem>()->OnWoodAxed.AddUObject(this, &AMyCharacter::Skill1ExpUpdate);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnEarthGroundPloughed.AddUObject(this, &AMyCharacter::Skill2ExpUpdate);
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnGrassGroundMowed.AddUObject(this, &AMyCharacter::Skill3ExpUpdate);

	CharacterRotation = FRotator(0.0f, 90.0f, 0.0f);
	SpringRotation = FRotator(-45.0f, -90.0f, 0.0f);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Player_Exp+=0.1f;
	if(Player_Exp>=Player_MaxExp){
		Hero_Level++;
		Player_Exp = 0;
		Player_MaxExp = experience_table[Hero_Level];
		UE_LOG(LogTemp, Warning, TEXT("Level Up !Exp to next Level:%d"), Player_MaxExp);
	}

	UpdateCharacterRotation();
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

	//BindSetFlagFunction
	PlayerInputComponent->BindAction(FName("SetMoveYFlag1"), IE_Pressed, this, &AMyCharacter::SetMoveYFlag1);
	PlayerInputComponent->BindAction(FName("SetMoveYFlag2"), IE_Pressed, this, &AMyCharacter::SetMoveYFlag2);
	PlayerInputComponent->BindAction(FName("SetMoveXFlag1"), IE_Pressed, this, &AMyCharacter::SetMoveXFlag1);
	PlayerInputComponent->BindAction(FName("SetMoveXFlag2"), IE_Pressed, this, &AMyCharacter::SetMoveXFlag2);

	//BindResetFlagFunction
	PlayerInputComponent->BindAction(FName("ResetMoveYFlag"), IE_Released, this, &AMyCharacter::ResetMoveYFlag);
	PlayerInputComponent->BindAction(FName("ResetMoveXFlag"), IE_Released, this, &AMyCharacter::ResetMoveXFlag);

	//Bind Equipment Functions
	PlayerInputComponent->BindAction(FName("Equip1"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut1);
	PlayerInputComponent->BindAction(FName("Equip2"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut2);
	PlayerInputComponent->BindAction(FName("Equip3"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut3);
	PlayerInputComponent->BindAction(FName("Equip4"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut4);
	PlayerInputComponent->BindAction(FName("Equip5"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut5);
	PlayerInputComponent->BindAction(FName("Equip6"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut6);
	PlayerInputComponent->BindAction(FName("Equip7"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut7);
	PlayerInputComponent->BindAction(FName("Equip8"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut8);
	PlayerInputComponent->BindAction(FName("Equip9"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut9);
	PlayerInputComponent->BindAction(FName("Equip10"), IE_Pressed, this, &AMyCharacter::CharacterSelectShortcut10);

	//Bind Mouse Click
	PlayerInputComponent->BindAction(FName("Click"), IE_Pressed, this, &AMyCharacter::MouseClick);

	//Bind Skill Functions
	PlayerInputComponent->BindAction(FName("Skill1"), IE_Pressed, this, &AMyCharacter::UseSkill1);
	PlayerInputComponent->BindAction(FName("Skill2"), IE_Pressed, this, &AMyCharacter::UseSkill2);
	PlayerInputComponent->BindAction(FName("Skill3"), IE_Pressed, this, &AMyCharacter::UseSkill3);

	//Call the Menu
	PlayerInputComponent->BindAction(FName("Menu"), IE_Pressed, this, &AMyCharacter::CallMenu);
}

void AMyCharacter::SetMoveYFlag1() {
	MoveYFlag = 1;
}

void AMyCharacter::SetMoveYFlag2() {
	MoveYFlag = -1;
}

void AMyCharacter::SetMoveXFlag1() {
	MoveXFlag = 1;
}

void AMyCharacter::SetMoveXFlag2() {
	MoveXFlag = -1;
}

void AMyCharacter::ResetMoveYFlag() { 
	MoveYFlag = 0;
}

void AMyCharacter::ResetMoveXFlag() {
	MoveXFlag = 0;
}

void AMyCharacter::UpdateCharacterRotation() {
	if (MoveXFlag == 0 && MoveYFlag == 0){
		this->SetActorRotation(CharacterRotation);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}

	if (MoveXFlag == 0 && MoveYFlag == 1) {
		CharacterRotation = FRotator(0.0f, 0.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, 0.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == 0 && MoveYFlag == -1) {
		CharacterRotation = FRotator(0.0f, 180.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, -180.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == 1 && MoveYFlag == 0) {
		CharacterRotation = FRotator(0.0f, -90.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, 90.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == -1 && MoveYFlag == 0) {
		CharacterRotation = FRotator(0.0f, 90.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, -90.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == 1 && MoveYFlag == 1) {
		CharacterRotation = FRotator(0.0f, -45.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, 45.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == -1 && MoveYFlag == 1) {
		CharacterRotation = FRotator(0.0f, 45.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, -45.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == 1 && MoveYFlag == -1) {
		CharacterRotation = FRotator(0.0f, -135.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, 135.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
	
	if (MoveXFlag == -1 && MoveYFlag == -1) {
		CharacterRotation = FRotator(0.0f, 135.0f, 0.0f);
		this->SetActorRotation(CharacterRotation);
		SpringRotation = FRotator(-45.0f, -135.0f, 0.0f);
		SpringArmComponent->SetRelativeRotation(SpringRotation);
		return;
	}
}

void AMyCharacter::MoveY(float Value)
{
	Direction = FVector(0.f, 1.f, 0.f);
	AddMovementInput(Direction, 1.5 * Value);
}

void AMyCharacter::MoveX(float Value)
{
	Direction = FVector(1.f, 0.f, 0.f);
	AddMovementInput(Direction, 1.5 * Value);
}

void AMyCharacter::MoveUp(float Value)
{
	SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, Value));
}

void AMyCharacter::CharacterSelectShortcut1() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut1"));
	now_shortcut_ = 1;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut2() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut2"));
	now_shortcut_ = 2;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut3() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut3"));
	now_shortcut_ = 3;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut4() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut4"));
	now_shortcut_ = 4;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut5() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut5"));
	now_shortcut_ = 5;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut6() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut6"));
	now_shortcut_ = 6;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut7() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut7"));
	now_shortcut_ = 7;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut8() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut8"));
	now_shortcut_ = 8;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut9() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut9"));
	now_shortcut_ = 9;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
}
void AMyCharacter::CharacterSelectShortcut10() {
	UE_LOG(LogTemp, Warning, TEXT("Select Shortcut10"));
	now_shortcut_ = 10;
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnShortcutSelected.Broadcast(now_shortcut_);
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
	UE_LOG(LogTemp, Warning, TEXT("Now Shortcut: %d"), now_shortcut_);

	//now_item_id is the exact type of the tool
	int32 now_item_id = GetGameInstance()->GetSubsystem<UDataSystem>()->getShortBar(now_shortcut_);
	UE_LOG(LogTemp, Warning, TEXT("Now Item Id: %d"), now_item_id);
	if (now_item_id == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Shortcut Now Is Empty"));
		return;
	}
	FStruct_ItemBase* item_info = item_data_table->FindRow<FStruct_ItemBase>(FName(*FString::FromInt(now_item_id)), "");

	float now_item_range = item_info->use_area;

	float skill_add_range = 0.0f;
	if(now_item_id == 20||now_item_id == 24)
		skill_add_range = axe_range_;
	if (now_item_id == 21 || now_item_id == 25)
		skill_add_range = hoe_range_;
	if (now_item_id == 22 || now_item_id == 26)
		skill_add_range = scythe_range_;
	float permit_range = now_item_range + skill_add_range;

	float distance = sqrt(pow(Location.X - CharacterLocation.X, 2) + pow(Location.Y - CharacterLocation.Y, 2));

	UE_LOG(LogTemp, Warning, TEXT("Permit Range: %f"), permit_range);
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);

	if (permit_range - distance > KINDA_SMALL_NUMBER) {
		if (now_item_id == 21 || now_item_id == 25)//item is tool->hoe
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnPloughingEarthGround.Broadcast(Location.X, Location.Y);

		if (now_item_id == 22 || now_item_id == 26)//item is tool->scythe
			GetGameInstance()->GetSubsystem<UEventSystem>()->OnMowingGrassGround.Broadcast(Location.X, Location.Y);

		GetGameInstance()->GetSubsystem<UEventSystem>()->OnToolsTowardsItemBlock.Broadcast(now_item_id, Location.X, Location.Y);
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
	axe_range_ = axe_level * 50.f;
	GetWorldTimerManager().SetTimer(AxeEndTimerHandle, this, &AMyCharacter::AxeSkillEnd, axe_duration);
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
	hoe_range_ = hoe_level * 50.f;
	GetWorldTimerManager().SetTimer(HoeEndTimerHandle, this, &AMyCharacter::HoeSkillEnd, hoe_duration);
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
	scythe_range_ = scythe_level * 50.f;
	GetWorldTimerManager().SetTimer(ScytheEndTimerHandle, this, &AMyCharacter::ScytheSkillEnd, scythe_duration);
	GetWorldTimerManager().SetTimer(ScytheTimerHandle, this, &AMyCharacter::ScytheEndCoolDown, scythe_cool_down_duration);
}

void AMyCharacter::Skill1ExpUpdate(){
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnSkillExpUpdate.Broadcast(1, 20);
}

void AMyCharacter::Skill2ExpUpdate() {
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnSkillExpUpdate.Broadcast(2, 20);
}

void AMyCharacter::Skill3ExpUpdate() {
	GetGameInstance()->GetSubsystem<UEventSystem>()->OnSkillExpUpdate.Broadcast(3, 20);
}

void AMyCharacter::AxeSkillEnd() {
	UE_LOG(LogTemp, Warning, TEXT("Skill1End"));
	axe_range_ = 0.f;
}

void AMyCharacter::HoeSkillEnd() {
	UE_LOG(LogTemp, Warning, TEXT("Skill2End"));
	hoe_range_ = 0.f;
}

void AMyCharacter::ScytheSkillEnd() {
	UE_LOG(LogTemp, Warning, TEXT("Skill2End"));
	scythe_range_ = 0.f;
}

void AMyCharacter::AxeEndCoolDown() {
	bIsAxeCoolDown = false;
	GetWorldTimerManager().ClearTimer(AxeTimerHandle);
}

void AMyCharacter::HoeEndCoolDown() {
	bIsHoeCoolDown = false;
	GetWorldTimerManager().ClearTimer(HoeTimerHandle);
}

void AMyCharacter::ScytheEndCoolDown() {
	bIsScytheCoolDown = false;
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