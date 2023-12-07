// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Exercise5.generated.h"

UCLASS()
class MATH_API AExercise5 : public AActor
{
	GENERATED_BODY()

public:
	AExercise5();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	AActor* InterpolationObject1;

	UPROPERTY(EditAnywhere)
	AActor* InterpolationObject2;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	double T = 0.5;

	UPROPERTY(EditAnywhere, meta=(ClampMin=0, UIMin=0))
	double NoiseStrength = 1;

	void MyTransformInterpolation();

	UFUNCTION(CallInEditor)
	void RegeneratePosition()
	{
		MyTransformInterpolation();
	}
};
