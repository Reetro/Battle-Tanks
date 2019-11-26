// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();

  auto PlayerTank = GetPlayerTank();
  if (!PlayerTank)
  {
    UE_LOG(LogTemp, Warning, TEXT("Couldn't Find Player Tank"));
  }
  else
  {
    UE_LOG(LogTemp, Log, TEXT("AIController Found Player: %s"), *(PlayerTank->GetName()));
  }
}
 
void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  if (GetPlayerTank())
  {
    // TODO Move to player

    // Aim at player tank
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
  }
}

ATank* ATankAIController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
  auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if (!PlayerPawn) { return nullptr; }
  return Cast<ATank>(PlayerPawn);
}
