// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TankBarrel.generated.h"

/**
 * TankBarrel is ued to Elevate the barrel and control how far it can up and down. It also controls the speed it can move.
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETTANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  // -1 is max downward movement and +1 is max up movement
  void Elevate(float RelativeSpeed);
private:
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MaxDegressPerSecond = 10;
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MinElevationDegrees = 0;
  UPROPERTY(EditDefaultsOnly, Category = Setup)
  float MaxElevationDegrees = 40;
};
