// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETTANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
  void LaunchProjectile(float LaunchSpeed);

private:
  UProjectileMovementComponent* ProjectialMovement = nullptr;

  UPROPERTY(VisibleAnywhere, Category = Collision)
  UStaticMeshComponent* CollisionMesh = nullptr;

  UPROPERTY(VisibleAnywhere, Category = Effects)
  UParticleSystemComponent* LaunchBlast = nullptr;

  UPROPERTY(VisibleAnywhere, Category = Effects)
  UParticleSystemComponent* ImpactBlast = nullptr;

  UPROPERTY(VisibleAnywhere, Category = Effects)
  URadialForceComponent* ExplosionForce = nullptr;

  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
