// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  if (!LeftTrackToSet || !RightTrackToSet) { return; }

  LeftTrack = LeftTrackToSet;
  RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveFoward(float Throw)
{
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
  UE_LOG(LogTemp, Log, TEXT("Throw: %f"), Throw)
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
}
