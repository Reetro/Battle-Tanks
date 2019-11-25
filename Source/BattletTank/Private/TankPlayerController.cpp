// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();

  auto ControlledTank = GetControlledTank();
  if (!ControlledTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("PlayController not possesing a tank"));
  }
  else
  {
    UE_LOG(LogTemp, Log, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
  }
}

void ATankPlayerController::Tick( float DeltaTime )
{
  Super::Tick( DeltaTime );
  AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetControlledTank()) { return; }

  FVector OutHitLocation; // Out Parameter

  if (GetSightRayHitLocation(OutHitLocation))
  {
    UE_LOG(LogTemp, Log, TEXT("Hit locations is: %s"), ( *OutHitLocation.ToString() ));
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
  if (GetLookDirection( ScreenLocation, LookDirection ))
  {
     GetVectorHitLocation(LookDirection, OutHitLocation);
  }
  return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
  FVector CameraWorldLocation; // To Be Discarded
  return DeprojectScreenPositionToWorld(
    ScreenLocation.X, 
    ScreenLocation.Y, 
    CameraWorldLocation, 
    LookDirection
  );
}

bool ATankPlayerController::GetVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
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
  return false;
}
