/*****************************************************************
 * \file   GroundBlockBase.h
 * \brief  The ground block base. A base class for ground blocks
 * 
 * \author 4_of_Diamonds
 * \date   November 2024
 *********************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundBlockBase.generated.h"

UCLASS()
class STARDEWVALLEY_API AGroundBlockBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* ground_mesh_;
	struct
	{
		float pos_x_, pos_y_;
	} position_;
public:	
	// Sets default values for this actor's properties
	AGroundBlockBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
