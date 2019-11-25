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

bool ATankPlayerController::GetSightRayHitLocation( FVector& OutHitLocation ) const
{
  OutHitLocation = FVector(1.0);
  return true;
}

void ATankPlayerController::AimTowardsCrossHair()
{
  if (!GetControlledTank()) { return; }

  FVector OutHitLocation; // Out Parameter

  if (GetSightRayHitLocation( OutHitLocation ))
  {
    UE_LOG(LogTemp, Log, TEXT("Hit locations is: %s"), ( *OutHitLocation.ToString() ));
  }
}
