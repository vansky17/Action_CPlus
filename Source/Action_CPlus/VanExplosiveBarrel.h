// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "VanExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;
class UAudioComponent;

UCLASS()
class ACTION_CPLUS_API AVanExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	AVanExplosiveBarrel();

	// 🔥 Built-in damage entry point
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> BarrelMesh;

	// Burning FX (looped)
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> BurningEffect;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> BurningSound;

	// Explosion FX
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;
private:
	// State
	bool bHasExploded = false;

	// Burning audio instance
	UPROPERTY()
	TObjectPtr<UAudioComponent> BurningAudioComp;

	// Timer
	FTimerHandle ExplosionTimerHandle;

	// Helpers
	void StartBurning();
	void Explode();
};
