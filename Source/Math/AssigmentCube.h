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
	AAssigmentCube();
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	virtual void BeginPlay() override;

	public:
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
