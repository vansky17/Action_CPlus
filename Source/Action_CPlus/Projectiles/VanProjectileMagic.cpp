// Fill out your copyright notice in the Description page of Project Settings.


#include "VanProjectileMagic.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AVanProjectileMagic::AVanProjectileMagic()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComponent;	
	SphereComponent->SetSphereRadius(17.0f);
	SphereComponent->SetCollisionProfileName("Projectile");
	
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LoopedNiagaraComp");
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
	
	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>("LoopedAudioComponent");
	LoopedAudioComponent->SetupAttachment(SphereComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

void AVanProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentHit.AddDynamic(this, &AVanProjectileMagic::OnActorHit);
	//SphereComponent->IgnoreActorWhenMoving(GetInstigator(),true);
}
void AVanProjectileMagic::OnActorHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (!OtherActor || !OtherComp)
		return;

	if (OtherComp->IsSimulatingPhysics())
	{
		const FVector ShotDirection = GetVelocity().GetSafeNormal();

		UGameplayStatics::ApplyPointDamage(
			OtherActor,
			10.f,
			ShotDirection,
			Hit,
			GetInstigatorController(),
			this,
			DmgTypeClass
		);
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		ExpostionEffect,
		Hit.ImpactPoint
	);

	UGameplayStatics::PlaySoundAtLocation(
		this,
		ExplosionSound,
		Hit.ImpactPoint
	);

	Destroy();
}

void AVanProjectileMagic::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* Pawn = GetInstigator())
	{
		SphereComponent->IgnoreActorWhenMoving(Pawn, true);
	}
}