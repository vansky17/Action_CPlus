// Fill out your copyright notice in the Description page of Project Settings.


#include "VanActionSystemComponent.h"


// Sets default values for this component's properties
UVanActionSystemComponent::UVanActionSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UVanActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;
	/*Attributes.Health += InValueChange;*/
	
	float MaxHealth = 100.0f;
	GetDefault<UVanActionSystemComponent>()->Attributes.Health;
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f"), Attributes.Health)
}


// Called when the game starts
void UVanActionSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVanActionSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

