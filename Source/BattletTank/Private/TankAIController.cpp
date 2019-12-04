// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}
 
void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // Get Player
  auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
  // Get Current Tank
  auto ControlledTank = Cast<ATank>(GetPawn());

  if (ensure(PlayerTank))
  {
    // TODO Move to Player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
    // Aim At Player
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    ControlledTank->FireGun();
  }   
}
