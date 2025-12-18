// Fill out your copyright notice in the Description page of Project Settings.


#include "VanPlayerController.h"

#include "EnhancedInputComponent.h"
#include "VanInteractionComponent.h"

AVanPlayerController::AVanPlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UVanInteractionComponent>("InteractionComp");
}

void AVanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &AVanPlayerController::StartInteract);
}

void AVanPlayerController::StartInteract()
{
	InteractionComponent->Interact();
}