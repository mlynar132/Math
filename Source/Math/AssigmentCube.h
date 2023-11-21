// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssigmentCube.generated.h"

class UTextRenderComponent;

UENUM(meta=(BitFlags))
enum class EMyEnum : uint8
{
	Above = 1 << 0,
	Right = 1 << 1,
	Forward = 1 << 2
};

ENUM_CLASS_FLAGS(EMyEnum)

UCLASS()
class MATH_API AAssigmentCube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAssigmentCube();
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
	AActor* Target;

	UPROPERTY(EditAnywhere, meta=(Bitmask, BitmaskEnum = EMyEnum))
	int32 Ehehehe = 0;
};
