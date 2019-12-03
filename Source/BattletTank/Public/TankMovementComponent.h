// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsable for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETTANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
  UFUNCTION(BlueprintCallable, Category = Setup)
  void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
  UFUNCTION(BlueprintCallable, Category = Input)
  void IntendMoveFoward(float Throw);
  UFUNCTION(BlueprintCallable, Category = Input)
  void IntendTurn(float Throw);

virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
  UTankTrack* LeftTrack = nullptr;
  UTankTrack* RightTrack = nullptr;
};