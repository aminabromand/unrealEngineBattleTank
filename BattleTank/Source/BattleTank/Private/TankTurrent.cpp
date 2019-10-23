// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurrent.h"

void UTankTurrent::Rotate(float RelativeSpeed) {
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel Elevate called at speed %f"), Time, RelativeSpeed);

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;


	SetRelativeRotation(FRotator(0, NewRotation, 0));
}