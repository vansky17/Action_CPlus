// Fill out your copyright notice in the Description page of Project Settings.


#include "VanPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../Projectiles/VanProjectile.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVanPlayerCharacter::AVanPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	MuzzleSocketName = "Muzzle_01";
	
	
}

void AVanPlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	//Forward, Back
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	//Sideways
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void AVanPlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void AVanPlayerCharacter::Jump(const FInputActionValue& InValue)
{

		Super::Jump();
}

void AVanPlayerCharacter::StartProjectileAttack(TSubclassOf<AVanProjectile> ProjectileClass)
{
	PlayAnimMontage(AttackMontage);
	
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName, FVector::ZeroVector, FRotator::ZeroRotator,
	EAttachLocation::Type::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;

	// Passing in the projectile as the parameter
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AVanPlayerCharacter::AttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, false);
	
}

void AVanPlayerCharacter::AttackTimerElapsed(
	TSubclassOf<AVanProjectile> ProjectileClass)
{
	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ProjectileClass is NULL"));
		return;
	}

	const AVanProjectile* ProjectileCDO =
		ProjectileClass->GetDefaultObject<AVanProjectile>();

	const FVector SpawnOffset = ProjectileCDO
		? ProjectileCDO->GetSpawnOffset()
		: FVector::ZeroVector;

	const FTransform MuzzleTransform =
		GetMesh()->GetSocketTransform(MuzzleSocketName, RTS_World);

	FVector SpawnLocation =
		MuzzleTransform.TransformPosition(SpawnOffset);

	FRotator SpawnRotation = MuzzleTransform.Rotator();

	// Push slightly forward to avoid overlap
	SpawnLocation += SpawnRotation.Vector() * 30.f;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AVanProjectile>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);
}


// Called when the game starts or when spawned
void AVanPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVanPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVanPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AVanPlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &AVanPlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Started, this, &AVanPlayerCharacter::Jump);
	// Projectile Attacks
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this,
		&AVanPlayerCharacter::StartProjectileAttack, PrimaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this,
		&AVanPlayerCharacter::StartProjectileAttack, SecondaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this,
		&AVanPlayerCharacter::StartProjectileAttack, SpecialAttackProjectileClass);
}
//Test only
