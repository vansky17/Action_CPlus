// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VanProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "VanProjectileMagic.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UAudioComponent;

UCLASS()
class ACTION_CPLUS_API AVanProjectileMagic : public AVanProjectile
{
	GENERATED_BODY()
protected:
	

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;
	
public:	
	
	// Sets default values for this actor's properties
	AVanProjectileMagic();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
