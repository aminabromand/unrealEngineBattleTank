// Copyright AbromandIT

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts or when spawned
void UTankAimingComponent::BeginPlay() {
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds;
	
	if (RoundsLeft <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}
	else if(isReloaded) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) return false;

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if (!ensure(Barrel)) return;
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
} 

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!Barrel || !Turrent) return;
	
	auto BarrelRotator = Barrel->GetForwardVector().GetSafeNormal().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180.0) {
		Turrent->Rotate(DeltaRotator.Yaw);
	}else {
		Turrent->Rotate(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire() {

	if (!ensure(Barrel && ProjectileBlueprint)) return;

	if(FiringState == EFiringState::Reloading) return;
	if (FiringState == EFiringState::OutOfAmmo) return;

	LastFireTime = FPlatformTime::Seconds();

	auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);
	Projectile->LaunchProjectile(LaunchSpeed);
	RoundsLeft--;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet) {
	if (BarrelToSet) Barrel = BarrelToSet;
	if (TurrentToSet) Turrent = TurrentToSet;
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const {
	return RoundsLeft;
}
