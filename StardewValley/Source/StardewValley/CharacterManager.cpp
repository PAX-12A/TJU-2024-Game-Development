// Fill out your copyright notice in the Description page of Project Settings.
/*********************************************************************
 * \file   CharacterManager.cpp
 * \brief  The Declaration of the character manager class
 *
 * \author magician
 * \date   December 2024
 *********************************************************************/

#include "CharacterManager.h"
#include "MyCharacter.h"
#include "NPC_Character.h"

void UCharacterManager::CharacterGenerate() {
	UE_LOG(LogTemp, Warning, TEXT("Character Generate"));

	UClass* AMyCharacterClass = LoadObject<UClass>(nullptr, TEXT("/Game/Character/BP_TestCharacter.BP_TestCharacter_C"));
	FVector SpawnLocation = FVector(1000.0f, 5500.0f, 300.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	AMyCharacter* CharacterInstance = World->SpawnActor<AMyCharacter>(AMyCharacterClass, SpawnLocation, SpawnRotation);

	UClass* ANPC_CharacterClass = LoadObject<UClass>(nullptr, TEXT("/Game/Character/BP_NPC_Character.BP_NPC_Character_C"));
	FVector SpawnLocation1 = FVector(1400.0f, 5500.0f, 75.0f);
	FRotator SpawnRotation1 = FRotator(0.0f, 0.0f, 0.0f);
	ANPC_Character* NPC_CharacterInstance1 = World->SpawnActor<ANPC_Character>(ANPC_CharacterClass, SpawnLocation1, SpawnRotation1);

	// Set Auto Possess Player to Player 0
	GetWorld()->GetFirstPlayerController()->Possess(CharacterInstance);
}

void UCharacterManager::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Warning, TEXT("CharacterManager Initialize"));
	
	UEventSystem* EventSystem = Collection.InitializeDependency<UEventSystem>();

	EventSystem->OnGroundGenerated.AddUObject(this, &UCharacterManager::CharacterGenerate);
}

void UCharacterManager::CharacterSave(){

}

void UCharacterManager::CharacterLoad(){

}