// Fill out your copyright notice in the Description page of Project Settings.


#include "VanItemChest.h"


// Sets default values
AVanItemChest::AVanItemChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	RootComponent = BaseMeshComponent;
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComponent"));
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

// Called when the game starts or when spawned
void AVanItemChest::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);
}

// Called every frame
void AVanItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	CurrentAnimationPitch = FMath::FInterpConstantTo(CurrentAnimationPitch, AnimationTargetPitch, DeltaTime, 50.0f);
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentAnimationPitch, 0.0f, 0.0f));
	
	if (FMath::IsNearlyEqual(CurrentAnimationPitch, AnimationTargetPitch))
	{
		SetActorTickEnabled(false);
	}
}

