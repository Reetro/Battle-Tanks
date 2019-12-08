// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETTANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

  virtual void BeginPlay() override;

  virtual void Tick(float DeltaTime) override;

protected:

  // How close can the AI tank can get
  UPROPERTY(EditDefaultsOnly, Category = Navigation)
  float AcceptanceRadius = 8000.0;

private:

  virtual void SetPawn(APawn* InPawn) override;

  UFUNCTION()
  void OnPossedTankDeath();
};
