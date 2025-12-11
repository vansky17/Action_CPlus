// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "VanCharacter.generated.h"

class AVanProjectileMagic;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
UCLASS(Abstract)
class ACTION_CPLUS_API AVanCharacter : public ACharacter
{
	GENERATED_BODY()
 
public:
	// Sets default values for this character's properties
	AVanCharacter();
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVanProjectileMagic> ProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> CastingEffect;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> CastingSound;
	
	UPROPERTY(VisibleAnywhere, Category="PrimaryAttack");
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> AttackMontage; 
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	
	UPROPERTY(VisibleAnywhere, Category="Components");
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components");
	TObjectPtr<USpringArmComponent> SpringArmComp;
	
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	
	void PrimaryAttack();
	void AttackTimerElapsed();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
