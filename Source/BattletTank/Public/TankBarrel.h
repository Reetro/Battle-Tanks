// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETTANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
  void Elevate(float DegressPerSecond);
private:
  UPROPERTY(EditAnyWhere, Category = Setup)
  float MaxDegressPerSecond = 20;
  UPROPERTY(EditAnyWhere, Category = Setup)
  float MinElevationDegrees = 0;
  UPROPERTY(EditAnyWhere, Category = Setup)
  float MaxElevationDegrees = 40;
};
