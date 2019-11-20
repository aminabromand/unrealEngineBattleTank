// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual UTankAimingComponent * GetAimingComponent() const;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void AimTowardsCrosshair();
	virtual bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	virtual bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	virtual bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

private:

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
};
