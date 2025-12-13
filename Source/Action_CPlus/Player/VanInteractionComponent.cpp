// Fill out your copyright notice in the Description page of Project Settings.


#include "VanInteractionComponent.h"


// Sets default values for this component's properties
UVanInteractionComponent::UVanInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVanInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UVanInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController> ( GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation(); 
	DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Red, false);

	// ...
}

