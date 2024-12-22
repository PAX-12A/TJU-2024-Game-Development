// Fill out your copyright notice in the Description page of Project Settings.


#include "Marketmanager.h"

void UMarketmanager::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("CharacterManager Initialize"));
	//while (1) {
		getInfo(1);
		Sell();
	//}
}