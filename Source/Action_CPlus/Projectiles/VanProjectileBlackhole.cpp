// Fill out your copyright notice in the Description page of Project Settings.


#include "VanProjectileBlackhole.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AVanProjectileBlackhole::AVanProjectileBlackhole()
{
	RadialForceComponent =
		CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(SphereComponent);

	RadialForceComponent->ForceStrength = -800000.0f;
	RadialForceComponent->Radius = 1200.0f;
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->bIgnoreOwningActor = true;

	RadialForceComponent->RemoveObjectTypeToAffect(
		UEngineTypes::ConvertToObjectType(ECC_Pawn));

	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("BlackholeCore");

	ProjectileMovementComponent->InitialSpeed = 500.0f;

	InitialLifeSpan = 5.0f;
}
void AVanProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Note: Make sure GenerateOverlapEvents is enabled on the cubes in the world
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AVanProjectileBlackhole::OnSphereOverlappedActor);
	
}

void AVanProjectileBlackhole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}
// Called when the game starts or when spawned
void AVanProjectileBlackhole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVanProjectileBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

