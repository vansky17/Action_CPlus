// Fill out your copyright notice in the Description page of Project Settings.


#include "VanExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"
#include "NiagaraFunctionLibrary.h"
// Sets default values
AVanExplosiveBarrel::AVanExplosiveBarrel()
{
	// Root component
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	SetRootComponent(BarrelMesh);

	// Physics & collision defaults (good barrel behavior)
	BarrelMesh->SetSimulatePhysics(true);
	BarrelMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	// 🔥 Radial force
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);

	RadialForceComp->Radius = 500.f;
	RadialForceComp->ImpulseStrength = 2000.f;
	RadialForceComp->bImpulseVelChange = true;   // ignores mass (usually desired)
	RadialForceComp->bAutoActivate = false;      // VERY important
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
}

// Called when the game starts or when spawned
float AVanExplosiveBarrel::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	if (bHasExploded)
	{
		return 0.f;
	}
	if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		if (PrimComp->IsSimulatingPhysics())
		{
			FVector ImpulseDir = FVector::UpVector;

			if (DamageCauser)
			{
				ImpulseDir = (GetActorLocation() - DamageCauser->GetActorLocation()).GetSafeNormal();
			}

			PrimComp->AddImpulse(ImpulseDir * 3000.f, NAME_None, true);
		}
	}
	// First time we take damage → start burning + countdown
	bHasExploded = true;

	StartBurning();

	// Delay explosion by 3 seconds
	GetWorldTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&AVanExplosiveBarrel::Explode,
		3.0f,
		false
	);

	return DamageAmount;
}
void AVanExplosiveBarrel::StartBurning()
{
	// Particle
	if (BurningEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(
			BurningEffect,
			BarrelMesh,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true
		);
	}

	// Looping sound
	if (BurningSound)
	{
		BurningAudioComp = UGameplayStatics::SpawnSoundAttached(
			BurningSound,
			BarrelMesh
		);
	}
}
void AVanExplosiveBarrel::Explode()
{
	// Stop burning sound
	if (BurningAudioComp)
	{
		BurningAudioComp->Stop();
	}

	// Explosion FX
	if (ExplosionEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ExplosionEffect,
		GetActorLocation()
);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ExplosionSound,
			GetActorLocation()
		);
	}
	// Stop burning FX
//	if (BurningNiagaraComp)
//	{
	//	BurningNiagaraComp->Deactivate();
//	}

	// 🔥 FIRE THE IMPULSE
	if (RadialForceComp)
	{
		RadialForceComp->FireImpulse();
	}

	// Explosion FX
	if (ExplosionEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ExplosionEffect,
			GetActorLocation()
		);
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ExplosionSound,
			GetActorLocation()
		);
	}

	Destroy();
}



