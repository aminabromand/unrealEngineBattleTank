// Copyright AbromandIT

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

	UPROPERTY(BlueprintReadWrite)
	UTankAimingComponent * TankAimingComponent = nullptr;

protected:
	UPROPERTY(BlueprintReadWrite)
	UTankBarrel* Barrel = nullptr;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
