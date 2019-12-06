// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
  Super::BeginPlay();

  OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

  // Work-out the required acceleration this frame to correct
  auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

  // Calculate and apply sideways (F = m a)
  auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
  auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks
  TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{ 
  auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
  auto ForceLocation = GetComponentLocation();
  auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  UE_LOG(LogTemp, Log, TEXT("Test"))
}
