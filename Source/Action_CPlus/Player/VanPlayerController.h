// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VanPlayerController.generated.h"

class UInputAction;
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
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Input_Interact;
	void StartInteract();
	
	virtual void SetupInputComponent() override;
	
public:
	AVanPlayerController();
};
