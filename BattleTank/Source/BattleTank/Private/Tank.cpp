// Copyright AbromandIT

#include "Tank.h"
//#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Engine/StaticMeshSocket.h"
#include "Projectile.h"


// Sets default values
ATank::ATank(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("12345 - Tank_Cpp: %s Constructor"), *TankName);
}

// Called when the game starts or when spawned
void ATank::BeginPlay(){
	Super::BeginPlay();
	auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("12345 - Tank_Cpp: %s BeginPlay"), *TankName);
}

void ATank::AimAt(FVector HitLocation) {
	if (!ensure(TankAimingComponent)) return;
	TankAimingComponent->AimAt(HitLocation);
} 

void ATank::Fire() {

	if (!ensure(Barrel && ProjectileBlueprint)) return;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (!isReloaded) return;

	

	LastFireTime = FPlatformTime::Seconds();

	auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);
	Projectile->LaunchProjectile(LaunchSpeed);
}

