#include "VanProjectileMagic.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"


AVanProjectileMagic::AVanProjectileMagic()
{
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
}

void AVanProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Keep the base implementation
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	FVector HitFromDirection = GetActorRotation().Vector();
	
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, HitFromDirection, Hit,  GetInstigatorController(),
		this, DmgTypeClass);
}
void AVanProjectileMagic::BeginPlay()
{
	Super::BeginPlay();
}