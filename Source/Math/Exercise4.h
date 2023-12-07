
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Exercise4.generated.h"

UCLASS()
class MATH_API AExercise4 : public AActor
{
	GENERATED_BODY()

public:
	AExercise4();

protected:
	virtual void BeginPlay() override;
	
	FVector Bounce(int32 BouncingObject, int32 Surface);
	FVector BounceFromWall(int32 BouncingObject);
	FVector RandomDirectionInSphere();

public:
	virtual void Tick(float DeltaTime) override;
	
	bool CheckForInterSectionBetween(AActor* Object1, AActor* Object2);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Object;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* IntersectionsMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NoIntersectionsMaterial;

	UPROPERTY()
	TArray<AActor*> Objects;

	UPROPERTY()
	TArray<FVector> Directions;

	UPROPERTY()
	TArray<float> Velocities;
	
	UPROPERTY()
	TArray<float> CollisionTimer;

	UPROPERTY(EditAnywhere)
	float ArenaRadius = 1000.0f;
	
	UFUNCTION(CallInEditor)
	void AddObject();

	UFUNCTION(CallInEditor)
	void RemoveObject();
};
