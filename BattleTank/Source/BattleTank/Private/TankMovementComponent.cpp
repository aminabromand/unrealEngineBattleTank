// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"


void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (LeftTrackToSet) LeftTrack = LeftTrackToSet;
	if (RightTrackToSet) RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: intend move forward: %f"), Time, Throw);

	if (LeftTrack) LeftTrack->SetThrottle(Throw);
	if (RightTrack) RightTrack->SetThrottle(Throw);
}