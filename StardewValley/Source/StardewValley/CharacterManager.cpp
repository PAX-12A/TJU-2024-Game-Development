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

void UCharacterManager::CharacterGenerate() {
	UE_LOG(LogTemp, Warning, TEXT("Character Generate"));
	UClass* AMyCharacterClass = LoadObject<UClass>(nullptr, TEXT("/Game/Character/BP_MyCharacter.BP_MyCharacter_C"));

	FVector SpawnLocation = FVector(-230.0f, 0.0f, 230.0f);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	UWorld* World = GetWorld();
	if (World == nullptr) return;
	AMyCharacter* CharacterInstance = World->SpawnActor<AMyCharacter>(AMyCharacterClass, SpawnLocation, SpawnRotation);
	// Set Auto Possess Player to Player 0
	GetWorld()->GetFirstPlayerController()->Possess(CharacterInstance);
	//CharacterInstance->AutoPossessPlayer = EAutoReceiveInput::Player0;
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