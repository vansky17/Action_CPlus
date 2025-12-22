// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VanProjectile.h"
#include "VanProjectileTeleport.generated.h"

UCLASS()
class ACTION_CPLUS_API AVanProjectileTeleport : public AVanProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVanProjectileTeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/* re-usable handle for the initial explosion delay and the teleportation (only 1 timer must be active) */
	FTimerHandle TeleportHandle;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float DetonateDelay = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	float TeleportSecondaryDelay = 0.2f;

	void StartDelayedTeleport();

	void HandleTeleportation();

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
