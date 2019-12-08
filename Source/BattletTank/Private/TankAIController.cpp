// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
  Super::BeginPlay();
}
 
void ATankAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // Get Player
  UWorld* World = GetWorld();
  auto PlayerTank = World->GetFirstPlayerController()->GetPawn();
  if (!PlayerTank) { return; }
  // Get Current Tank
  auto ControlledTank = GetPawn();

  if (!ensure(ControlledTank)) { return; }

  // TODO Move to Player
  MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
  // Aim At Player
  auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
  AimingComponent->AimAt(PlayerTank->GetActorLocation());
  if (AimingComponent->GetFiringState() == EFiringState::Locked)
  {
    AimingComponent->FireGun();
  }
}

void ATankAIController::SetPawn(APawn* InPawn)
{
  Super::SetPawn(InPawn);

  if (InPawn)
  {
    auto PossessedTank = Cast<ATank>(InPawn);
    if (!ensure(PossessedTank)) { return; }

    PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
  }
}

void ATankAIController::OnPossedTankDeath()
{
  if (!ensure(GetPawn())) { return; }
  GetPawn()->DetachFromControllerPendingDestroy();
}
