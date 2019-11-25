// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();

  auto ControlledTank = GetControlledTank();
  if (!ControlledTank)
  {
    UE_LOG(LogTemp, Log, TEXT("PlayController not possesing a tank"));
  }
  else
  {
    UE_LOG(LogTemp, Log, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
  }
}

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}
