// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "VanPlayerCharacter.generated.h"

class UVanActionSystemComponent;
class AVanProjectile;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;
UCLASS(Abstract)
class ACTION_CPLUS_API AVanPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
 
public:
	// Sets default values for this character's properties
	AVanPlayerCharacter();
protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVanProjectile> PrimaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<AVanProjectile> SecondaryAttackProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<AVanProjectile> SpecialAttackProjectileClass;
	
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
	TObjectPtr<UInputAction> Input_Jump;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;
	
	UPROPERTY(VisibleAnywhere, Category="Components");
	TObjectPtr<UCameraComponent> CameraComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components");
	TObjectPtr<USpringArmComponent> SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components");
	TObjectPtr<UVanActionSystemComponent> ActionSystemComponent;
	
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void Jump(const FInputActionValue& InValue);
	void  StartProjectileAttack(TSubclassOf<AVanProjectile> ProjectileClass);
	void AttackTimerElapsed(TSubclassOf<AVanProjectile> ProjectileClass);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; 
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
