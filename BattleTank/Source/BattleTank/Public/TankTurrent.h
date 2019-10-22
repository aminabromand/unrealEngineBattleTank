// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurrent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurrent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Turn(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxTurningDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinTurningDegrees = 0;
};
