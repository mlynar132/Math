#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Exercise3.generated.h"

UCLASS()
class MATH_API AExercise3 : public AActor
{
	GENERATED_BODY()

public:
	AExercise3();
	
	bool ShouldTickIfViewportsOnly() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	bool CheckForInterSectionBetween(AActor* Object1, AActor* Object2)const;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Object;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* IntersectionsMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* NoIntersectionsMaterial;

	UPROPERTY()
	TArray<AActor*> Objects;

	UFUNCTION(CallInEditor)
	void AddObject();

	UFUNCTION(CallInEditor)
	void RemoveObject();
};
