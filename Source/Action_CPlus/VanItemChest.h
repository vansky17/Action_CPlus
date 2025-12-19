// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/VanInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "VanItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTION_CPLUS_API AVanItemChest : public AActor, public IVanInteractionInterface
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this actor's properties
	AVanItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
    	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;
	
	UPROPERTY(EditAnywhere)
	float AnimationSpeed = 50.0f;
	UPROPERTY(EditAnywhere)
	float AnimationTargetPitch = 120.0f;
	
	float CurrentAnimationPitch = 0.0f;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ChestAnimationComplete();

public:
	// Called every frame
	virtual void Interact() override;
	
	virtual void Tick(float DeltaTime) override;
};
