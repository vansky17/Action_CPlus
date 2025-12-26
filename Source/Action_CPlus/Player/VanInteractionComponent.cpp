// Fill out your copyright notice in the Description page of Project Settings.


#include "VanInteractionComponent.h"

#include "Action_CPlus/VanGameTypes.h"
#include "Action_CPlus/Core/VanInteractionInterface.h"
#include "Engine/OverlapResult.h"


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


void UVanInteractionComponent::Interact()
{
	/*IVanInteractionInterface* InteractInterface = Cast<IVanInteractionInterface>(SelectedActor);
	if (InteractInterface)
	{
		InteractInterface->Interact();
	}*/
	IVanInteractionInterface::Execute_Interact(SelectedActor);
}

// Called every frame
void UVanInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController> ( GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation(); 
	
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	
	TArray<FOverlapResult> Overlaps;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	/*DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);*/
	
	AActor* BestActor = nullptr;
	float HighestDotResutl = -1.0;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		
		
		
		if (DotResult > HighestDotResutl)
		{
			BestActor = Overlap.GetActor();
			HighestDotResutl = DotResult;
		}
		/*DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red, false);
		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);*/
	}
	
	SelectedActor = BestActor;
	/*if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(70.0f), FColor::Green, false);
	}*/
}

