// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
  // Make sure the relative isn't above 1 or below -1
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
  // Frame-Rate independent
  auto RotationChange = RelativeSpeed * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
  auto Rotation = RelativeRotation.Yaw + RotationChange;
  SetRelativeRotation(FRotator(0, Rotation, 0));
}
