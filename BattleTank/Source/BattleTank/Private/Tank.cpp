// Copyright AbromandIT

#include "Tank.h"
//#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurrent.h"
#include "Engine/StaticMeshSocket.h"



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



