// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual ATank * GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void AimTowardsCrosshair();
	virtual bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	virtual bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	virtual bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

private:

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000000;
};