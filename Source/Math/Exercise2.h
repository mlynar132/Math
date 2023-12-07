
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Exercise2.generated.h"

UCLASS()
class MATH_API AExercise2 : public AActor
{
	GENERATED_BODY()
	
public:	
	AExercise2();

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
	float T = 0.5f;

	void MyTransformInterpolation();
};
