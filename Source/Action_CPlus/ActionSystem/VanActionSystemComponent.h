// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VanActionSystemComponent.generated.h"

struct FVanAttributeSet
{
	FVanAttributeSet()
		: Health(100.0f){}
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTION_CPLUS_API UVanActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UVanActionSystemComponent();
	void ApplyHealthChange (float InValueChange);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVanAttributeSet Attributes;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
