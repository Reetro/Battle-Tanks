// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

  ProjectialMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectialMovement"));
  ProjectialMovement->bAutoActivate = false;

  CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
  CollisionMesh->SetNotifyRigidBodyCollision(true);
  CollisionMesh->SetVisibility(false);
  RootComponent = CollisionMesh;

  LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
  LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

  ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
  ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
  ImpactBlast->bAutoActivate = false;

  ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
  ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::LaunchProjectile(float Speed)
{
  ProjectialMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
  ProjectialMovement->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

  CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  LaunchBlast->Deactivate();
  ImpactBlast->Activate();
  ExplosionForce->FireImpulse();

  SetRootComponent(ImpactBlast);
  CollisionMesh->DestroyComponent();

  UWorld* World = GetWorld();

  FTimerHandle Timer;
  World->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerFinish, DespawnDelay, false);
}

void AProjectile::OnTimerFinish()
{
  Destroy();
}
