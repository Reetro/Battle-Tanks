// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "UObject/Class.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"

// Fire State Enum
UENUM()
enum class EFiringState : uint8
{
  Locked,
  Aiming,
  Reloading
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETTANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

  UFUNCTION(BlueprintCallable, Category = Setup)
  void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

  void AimAt(FVector HitLocation);

protected:
  UPROPERTY(BlueprintReadOnly, Category = State)
  EFiringState FiringState = EFiringState::Reloading;

private:
  UTankBarrel* Barrel = nullptr; 
  UTankTurret* Turret = nullptr;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
  float LaunchSpeed = 4000;


  void MoveBarrelTowards(FVector AimDirection);
};
