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
#include "Engine/DataTable.h"
#include "Struct_ItemBase.h"
#include "TimerManager.h"
#include "EventSystem.h"
#include "DataSystem.h"
#include "MyCharacter.generated.h"

const static int32 experience_table[20] = { 10,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900 };

UCLASS()
class STARDEWVALLEY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere)
	int32 CharacterPosX;

	UPROPERTY(VisibleAnywhere)
	int32 CharacterPosY;

	UPROPERTY(VisibleAnywhere)
	int32 CharacterPosZ;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Hero_Level;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float Player_Exp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	int32 Player_MaxExp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Player_Money;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

private:
	void UpdateCharacterRotation();

	//Move in Y direction
	void MoveY(float Value);
	int32 MoveYFlag;
	void SetMoveYFlag1();
	void SetMoveYFlag2();
	void ResetMoveYFlag();

	//Move in X direction
	void MoveX(float Value);
	int32 MoveXFlag;
	void SetMoveXFlag1();
	void SetMoveXFlag2();
	void ResetMoveXFlag();

	FVector Direction;
	FRotator CharacterRotation;
	FRotator SpringRotation;

	//Move in Up direction
	void MoveUp(float Value);

	void CharacterSelectShortcut1();
	void CharacterSelectShortcut2();
	void CharacterSelectShortcut3();
	void CharacterSelectShortcut4();
	void CharacterSelectShortcut5();
	void CharacterSelectShortcut6();
	void CharacterSelectShortcut7();
	void CharacterSelectShortcut8();
	void CharacterSelectShortcut9();
	void CharacterSelectShortcut10();

	void MouseClick();

	void CharacterToolsUse(FVector Location);

	void UseSkill1();
	void UseSkill2();
	void UseSkill3();

	void Skill1ExpUpdate();
	void Skill2ExpUpdate();
	void Skill3ExpUpdate();

	void CallMenu();
	//void SkillLevelUpdate(int32 skill_experience,int32 skill_type);

	void CharacterLocationUpdate();

	int32 now_shortcut_ = 1;

	float axe_range_;
	float hoe_range_;
	float scythe_range_;

	float axe_duration = 3.0f;
	float hoe_duration = 3.0f;
	float scythe_duration = 3.0f;
	float axe_cool_down_duration = 5.0f;
	float hoe_cool_down_duration = 5.0f;
	float scythe_cool_down_duration = 5.0f;

	FTimerHandle AxeTimerHandle;
	FTimerHandle HoeTimerHandle;
	FTimerHandle ScytheTimerHandle;
	FTimerHandle AxeEndTimerHandle;
	FTimerHandle HoeEndTimerHandle;
	FTimerHandle ScytheEndTimerHandle;
	
	bool bIsAxeCoolDown = false;
	bool bIsHoeCoolDown = false;
	bool bIsScytheCoolDown = false;

	void AxeSkillEnd();
	void HoeSkillEnd();
	void ScytheSkillEnd();
	void AxeEndCoolDown();
	void HoeEndCoolDown();
	void ScytheEndCoolDown();

	UPROPERTY(VisibleAnywhere)
	FVector CharacterLocation;

	UDataTable* item_data_table = LoadObject<UDataTable>(nullptr, TEXT("/Game/Datatable/DT_ItemBase.DT_ItemBase"));

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
