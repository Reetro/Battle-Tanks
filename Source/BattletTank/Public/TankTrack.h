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

  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

  void ApplySideWaysForce();

  float CurrentThrottle = 0;

  void DriveTrack();

  virtual void BeginPlay() override;
};
