// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETTANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

  void AimAt(FVector HitLocation, float LaunchSpeed);

  void SetBarrelReferance(UTankBarrel* BarrelToSet);

private:
  UTankBarrel* Barrel = nullptr;

  void MoveBarrelTowards(FVector AimDirection);
};
