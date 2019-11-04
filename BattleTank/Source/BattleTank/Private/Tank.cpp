// Copyright AbromandIT

#include "Tank.h"
//#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Engine/StaticMeshSocket.h"
#include "Projectile.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay(){
	Super::BeginPlay();
}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
} 

void ATank::Fire() {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!Barrel || !isReloaded || !ProjectileBlueprint) return;

	LastFireTime = FPlatformTime::Seconds();

	auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);
	Projectile->LaunchProjectile(LaunchSpeed);
}

