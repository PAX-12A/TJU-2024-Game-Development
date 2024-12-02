// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBlockBase.generated.h"

UCLASS()
class STARDEWVALLEY_API AItemBlockBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* item_mesh_;
public:	
	// Sets default values for this actor's properties
	AItemBlockBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
