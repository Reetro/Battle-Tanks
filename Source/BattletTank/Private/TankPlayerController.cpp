// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick( float DeltaTime ) // Called every frame
{
  Super::Tick( DeltaTime );
  AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetPawn()) { return; } // if not possessing a tank return
  auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (!ensure(AimingComponent)) { return; }
  FVector OutHitLocation; // Out Parameter

  if (GetSightRayHitLocation(OutHitLocation))
  {
    AimingComponent->AimAt(OutHitLocation);
  }
}

bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{
  // Find postion of crosshair
  int32 ViewportX, ViewportY;
  GetViewportSize( ViewportX, ViewportY );
  auto ScreenLocation = FVector2D( ViewportX * CrossHairXLocation, ViewportY * CrossHairYLocation );
  // De project the screen location of the crosshair to get world direction
  FVector LookDirection;
  bool bGotHitLocation = GetLookDirection(ScreenLocation, LookDirection);
  if (bGotHitLocation)
  {
     return GetVectorHitLocation(LookDirection, OutHitLocation);
  }
  return false;
}

bool ATankPlayerController::GetLookDirection( FVector2D ScreenLocation, FVector& LookDirection ) const
{
  FVector CameraWorldLocation; // To Be Discarded
  return DeprojectScreenPositionToWorld(
    ScreenLocation.X, 
    ScreenLocation.Y, 
    CameraWorldLocation, 
    LookDirection
  );
}

bool ATankPlayerController::GetVectorHitLocation( FVector LookDirection, FVector& OutHitLocation ) const
{
  FHitResult HitResult;
  auto StartLocation = PlayerCameraManager->GetCameraLocation();
  auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
  if (GetWorld()->LineTraceSingleByChannel(
    HitResult,
    StartLocation,
    EndLocation,
    ECollisionChannel::ECC_Visibility)
    )
  {
    OutHitLocation = HitResult.Location;
    return true;
  }
  OutHitLocation = FVector(0);
  return false; // Linetrace hit nothing
}
