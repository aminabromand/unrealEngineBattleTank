// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
	virtual UTankAimingComponent * GetAimingComponent() const;
	virtual ATank* GetPlayerTank() const;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float AcceptanceRadius = 3000.0;
};
