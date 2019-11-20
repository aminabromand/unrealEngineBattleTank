// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"
//Depends on TankMovementComponent via Pathfinding


UTankAimingComponent* ATankAIController::GetAimingComponent() const {
	if (!GetPawn()) return NULL;
	return Cast<ATank>(GetPawn())->TankAimingComponent;
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return nullptr;
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {

		MoveToActor(PlayerTank, AcceptanceRadius);

		auto AimingComponent = GetAimingComponent();
		if (!AimingComponent) return;
		GetAimingComponent()->AimAt(GetPlayerTank()->GetActorLocation());
		GetAimingComponent()->Fire();
	}
}