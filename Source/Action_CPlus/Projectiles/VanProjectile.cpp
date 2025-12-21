// Fill out your copyright notice in the Description page of Project Settings.


#include "VanProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AVanProjectile::AVanProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComponent;	
	SphereComponent->SetSphereRadius(17.0f);
	SphereComponent->SetCollisionProfileName("Projectile");
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileComp");
	ProjectileMovementComponent->InitialSpeed = 2000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);

	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComp"));
	LoopedAudioComponent->SetupAttachment(SphereComponent);
	
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}
/*void AVanProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	PlayExplodeEffects();
	
	Destroy();
}*/

void AVanProjectile::PlayExplodeEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
}

void AVanProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &AVanProjectile::OnActorHit);
	//SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}
void AVanProjectile::OnActorHit(
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
	
	/*UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		this,
		ExpostionEffect,
		Hit.ImpactPoint
	);

	UGameplayStatics::PlaySoundAtLocation(
		this,
		ExplosionSound,
		Hit.ImpactPoint
	); */
	PlayExplodeEffects();
	Destroy();
}
// Called when the game starts or when spawned
void AVanProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* Pawn = GetInstigator())
	{
		SphereComponent->IgnoreActorWhenMoving(Pawn, true);
	}
}

// Called every frame
void AVanProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

