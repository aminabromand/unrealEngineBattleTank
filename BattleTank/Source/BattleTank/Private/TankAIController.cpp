// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"
//Depends on TankMovementComponent via Pathfinding


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
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

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		GetControlledTank()->Fire();
	}
}