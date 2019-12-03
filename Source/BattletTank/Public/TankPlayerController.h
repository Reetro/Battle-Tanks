// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETTANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

  virtual void BeginPlay() override;

  virtual void Tick( float DeltaTime ) override;

protected:
  UFUNCTION(BlueprintCallable, Category = Setup)
  ATank* GetControlledTank() const;

private:

  bool GetSightRayHitLocation( FVector& OutHitLocation ) const;

  void AimTowardsCrossHair(); // Move the tanks barrel to where the crosshair intersects the world

  UPROPERTY(EditDefaultsOnly)
  float CrossHairXLocation = 0.5;
  UPROPERTY(EditDefaultsOnly)
  float CrossHairYLocation = 0.3333;
  UPROPERTY(EditDefaultsOnly)
  float LineTraceRange = 1000000;

  bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

  bool GetVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};
