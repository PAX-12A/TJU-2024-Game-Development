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
#include "TimerManager.h"
#include "EventSystem.h"
#include "DataSystem.h"
#include "MyCharacter.generated.h"

const static int32 experience_table[20] = { 0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900 };

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

	void CharacterEquipTool1();
	void CharacterEquipTool2();
	void CharacterEquipTool3();
	void CharacterEquipTool4();
	void CharacterEquipTool5();
	void CharacterEquipTool6();
	void CharacterEquipTool7();
	void CharacterEquipTool8();
	void CharacterEquipTool9();
	void CharacterEquipTool10();

	void MouseClick();

	void CharacterToolsUse(FVector Location);

	void UseSkill1();
	void UseSkill2();
	void UseSkill3();

	void CallMenu();
	//void SkillLevelUpdate(int32 skill_experience,int32 skill_type);

	void CharacterLocationUpdate();

	int32 now_tool_;

	float default_axe_range_ = 200.0f;
	float default_hoe_range_ = 200.0f;
	float default_scythe_range_ = 200.0f;
	float axe_range_;
	float hoe_range_;
	float scythe_range_;

	float axe_cool_down_duration = 5.0f;
	float hoe_cool_down_duration = 5.0f;
	float scythe_cool_down_duration = 5.0f;

	FTimerHandle AxeTimerHandle;
	FTimerHandle HoeTimerHandle;
	FTimerHandle ScytheTimerHandle;
	
	bool bIsAxeCoolDown = false;
	bool bIsHoeCoolDown = false;
	bool bIsScytheCoolDown = false;

	void AxeEndCoolDown();
	void HoeEndCoolDown();
	void ScytheEndCoolDown();

	UPROPERTY(VisibleAnywhere)
	FVector CharacterLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
