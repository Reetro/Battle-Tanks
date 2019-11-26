// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
  // Make sure the relative isn't above 1 or below -1
  RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
  // Frame-Rate independent
  auto ElevationChange = RelativeSpeed * MaxDegressPerSecond * GetWorld()->DeltaTimeSeconds;
  auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
  auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
  SetRelativeRotation(FRotator(Elevation, 0, 0));
}
