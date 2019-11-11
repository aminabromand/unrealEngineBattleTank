// Copyright AbromandIT

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};

//The tanks barrel
class UTankBarrel;
class UTankTurrent;

//Helps the tank to aim
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);

protected:
	UPROPERTY(BluePrintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurrent* Turrent = nullptr;
	void MoveBarrelTowards(FVector AimDirection);	
};
