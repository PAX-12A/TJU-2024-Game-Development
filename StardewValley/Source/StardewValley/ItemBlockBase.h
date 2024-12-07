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
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* box_;
public:	
	// Sets default values for this actor's properties
	AItemBlockBase();
	void InitializeItemBlock(int32 id);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	int32 lived_time_;
	bool is_today_watered_;
	/**
	 * Grows the crop to the next stage.
	 *
	 */
	virtual void Grow();
	/**
	 * \brief Sets is_today_watered_ to false.
	 * 
	 */
	virtual void GetThirsty();
	/**
	 * Sets the appearance of the item block.
	 * 
	 * \param status The status of the item block
	 */
	virtual void SetAppearanceByStatus(int32 status);
public:
	/**
	 * \brief Water the crop.
	 *
	 */
	virtual void WaterThisCrop();
	/**
	 * To have rain waters this crop.
	 *
	 */
	virtual void RainWatersThisCrop();
};
