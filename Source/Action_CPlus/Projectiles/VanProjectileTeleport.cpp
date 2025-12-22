// Fill out your copyright notice in the Description page of Project Settings.


#include "VanProjectileTeleport.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"


// Sets default values
AVanProjectileTeleport::AVanProjectileTeleport()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMovementComponent->InitialSpeed = 6000.0f;
}

// Called when the game starts or when spawned
void AVanProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::StartDelayedTeleport, DetonateDelay);	
}
void AVanProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Skip the base implementation, we handle our own as we must delay destroying and avoid playing duplicate explosion effects
	//Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	// Cancel the timer to prevent a second teleportation
	GetWorldTimerManager().ClearTimer(TeleportHandle);
	
	StartDelayedTeleport();
}
void AVanProjectileTeleport::StartDelayedTeleport()
{
	PlayExplodeEffects();
	
	// Prevent moving us further ahead while we wait for the teleport to trigger
	ProjectileMovementComponent->StopMovementImmediately();
	// Hide all visuals and prevent any further collision while we wait on the teleport timer
	LoopedNiagaraComponent->Deactivate();
	LoopedAudioComponent->Stop();
	SetActorEnableCollision(false);
	
	// Another delay until we teleport (so player has a chance to see the VFX before we move them)
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::HandleTeleportation, TeleportSecondaryDelay);
}
void AVanProjectileTeleport::HandleTeleportation()
{
	APawn* ActorToTeleport = GetInstigator();
	if (!ActorToTeleport)
	{
		UE_LOG(LogTemp, Warning, TEXT("Teleport projectile has no instigator"));
		Destroy();
		return;
	}

	// Handles de-penetration on nearby collision geometry
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	// note: the teleport call might fail if it cannot find any valid location

	// Clear projectile from world, can't do this any sooner as that would prevent the timers from running on a valid Actor
	Destroy();
}
// Called every frame
void AVanProjectileTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

