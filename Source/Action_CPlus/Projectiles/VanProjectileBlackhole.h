// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VanProjectile.h"
#include "VanProjectileBlackhole.generated.h"

class URadialForceComponent;

UCLASS()
class ACTION_CPLUS_API AVanProjectileBlackhole : public AVanProjectile
{
	GENERATED_BODY()

public:
	
	virtual void PostInitializeComponents() override;
	AVanProjectileBlackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category= "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float SwirlStrength = 300000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float MaxPullStrength = -300000.0f;

	float CurrentPullStrength = -50000.0f;

	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
