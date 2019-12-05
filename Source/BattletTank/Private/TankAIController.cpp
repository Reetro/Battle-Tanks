// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}
 
void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // Get Player
  auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
  // Get Current Tank
  auto ControlledTank = GetPawn();

  if (!ensure(PlayerTank && ControlledTank)) { return; }

  // TODO Move to Player
  MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
  // Aim At Player
  auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
  AimingComponent->AimAt(PlayerTank->GetActorLocation());
  AimingComponent->FireGun();
}
