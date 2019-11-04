// Copyright AbromandIT

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (LeftTrackToSet) LeftTrack = LeftTrackToSet;
	if (RightTrackToSet) RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (LeftTrack) LeftTrack->SetThrottle(Throw);
	if (RightTrack) RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (LeftTrack) LeftTrack->SetThrottle(Throw);
	if (RightTrack) RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto TankName = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);
}