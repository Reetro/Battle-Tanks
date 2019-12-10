// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maxinum driving force, apply force to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETTANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable, Category = Input)
  void SetThrottle(float throttle);

private:
  UPROPERTY(EditDefaultsOnly)
  float TrackMaxDrivingForce = 400000;

  UTankTrack();

  void DriveTrack(float CurrentThrottle);

  TArray<class ASprungWheel*> GetWheels() const;
};
