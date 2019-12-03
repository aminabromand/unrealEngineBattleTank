// Copyright AbromandIT

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

//The tanks barrel
class UTankBarrel;
class UTankTurrent;
class AProjectile;

//Helps the tank to aim
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet);

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft() const;

protected:
	UPROPERTY(BluePrintReadOnly, Category = "Firing")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurrent* Turrent = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	virtual void BeginPlay() override;

	virtual bool IsBarrelMoving();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 30;
};
