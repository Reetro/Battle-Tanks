// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
  
void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
  Barrel = BarrelToSet;
  Turret = TurretToSet;
}


void UTankAimingComponent::BeginPlay()
{
  // Prevents firing as soon as the game starts
  LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
  {
    FiringState = EFiringState::Reloading;
  }
  else if (bIsBarrelMoving())
  {
    FiringState = EFiringState::Aiming;
  }
  else
  {
    FiringState = EFiringState::Locked;
  }
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
  if (!ensure(Barrel)) { return; }

  FVector OutLaunchVelocity(0);
  FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
  bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
  (
    this,
    OutLaunchVelocity,
    StartLocation,
    HitLocation,
    LaunchSpeed,
    false,
    0,
    0,
    ESuggestProjVelocityTraceOption::DoNotTrace
  );

  // Calcuate OutLaunchVelocity
  if (bHaveAimSolution)
  {
    AimDirection = OutLaunchVelocity.GetSafeNormal();
    MoveBarrelTowards(AimDirection);
  }
}

void UTankAimingComponent::FireGun()
{
  if (FiringState != EFiringState::Reloading)
  {
    if (!ensure(Barrel)) { return; }
    if (!ensure(ProjectileBlueprint)) { return; }
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(
      ProjectileBlueprint,
      Barrel->GetSocketLocation(FName("Projectile")),
      Barrel->GetSocketRotation(FName("Projectile"))
      );
    Projectile->LaunchProjectile(LaunchSpeed);
    LastFireTime = FPlatformTime::Seconds();
  }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  if (!ensure(Barrel && Turret)) { return; }
  auto BarrelRotator = Barrel->GetForwardVector().Rotation();
  auto AimAsRotator = AimDirection.Rotation();
  auto DeltaRotator = AimAsRotator - BarrelRotator;

  Barrel->Elevate(DeltaRotator.Pitch);
  Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::bIsBarrelMoving()
{
  if (!ensure(Barrel)) { return false; }
  auto BarrelFoward = Barrel->GetForwardVector();
  return !BarrelFoward.Equals(AimDirection, 0.01);
}
