// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//The tanks barrel
class UTankBarrel;
class UTankTurrent;
class UTankAimingComponent;
class AProjectile;


//The battle tank
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurrentReference(UTankTurrent* TurrentToSet);

	UFUNCTION(BlueprintCallable, Category = Combat)
		void Fire();

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000;

	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UTankBarrel* Barrel = nullptr;
};
