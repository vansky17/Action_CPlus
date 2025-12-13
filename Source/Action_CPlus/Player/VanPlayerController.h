// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VanPlayerController.generated.h"

class UVanInteractionComponent;
/**
 * 
 */
UCLASS()
class ACTION_CPLUS_API AVanPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UVanInteractionComponent> InteractionComponent;
	
public:
	AVanPlayerController();
};
