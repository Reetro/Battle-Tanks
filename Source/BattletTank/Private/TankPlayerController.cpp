// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

  if (AimingComponent)
  {
    FoundAimingComponent(AimingComponent);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find TankAimingComponent on event begin play"))
  }
}

void ATankPlayerController::Tick( float DeltaTime ) // Called every frame
{
  Super::Tick( DeltaTime );
  AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetControlledTank()) { return; }

  FVector OutHitLocation; // Out Parameter

  if (GetSightRayHitLocation(OutHitLocation))
  {
    GetControlledTank()->AimAt(OutHitLocation);
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

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}
