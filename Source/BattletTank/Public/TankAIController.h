// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

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

  // How close can the AI tank get
  float AcceptanceRadius = 3000;
};
