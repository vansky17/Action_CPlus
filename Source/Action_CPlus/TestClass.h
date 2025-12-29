// DELETE

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestClass.generated.h"

UCLASS()
class ACTION_CPLUS_API ATestClass : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
