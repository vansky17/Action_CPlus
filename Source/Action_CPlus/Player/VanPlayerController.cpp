// Fill out your copyright notice in the Description page of Project Settings.


#include "VanPlayerController.h"

#include "VanInteractionComponent.h"

AVanPlayerController::AVanPlayerController()
{
	InteractionComponent = CreateDefaultSubobject<UVanInteractionComponent>("InteractionComp");
}
