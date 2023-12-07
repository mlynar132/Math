#include "Exercise3.h"

AExercise3::AExercise3()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

bool AExercise3::ShouldTickIfViewportsOnly() const
{
	TArray<bool> IsIntersecting;
	for (int i = 0; i < Objects.Num(); i++)
	{
		IsIntersecting.Push(false);
	}
	for (int i = 0; i < Objects.Num() - 1; i++)
	{
		for (int j = i + 1; j < Objects.Num(); j++)
		{
			if (CheckForInterSectionBetween(Objects[i], Objects[j]))
			{
				IsIntersecting[i] = true;
				IsIntersecting[j] = true;
			}
		}
	}
	for (int i = 0; i < Objects.Num(); i++)
	{
		if (IsIntersecting[i])
		{
			Objects[i]->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, IntersectionsMaterial);
		}
		else
		{
			Objects[i]->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, NoIntersectionsMaterial);
		}
	}
	return Super::ShouldTickIfViewportsOnly();
}

void AExercise3::BeginPlay()
{
	Super::BeginPlay();
}

void AExercise3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExercise3::AddObject()
{
	Objects.Add(GetWorld()->SpawnActor<AActor>(Object, GetActorLocation(), FRotator::ZeroRotator));
}

void AExercise3::RemoveObject()
{
	if (!Objects.IsEmpty())
	{
		Objects.Pop()->Destroy();
	}
}

bool AExercise3::CheckForInterSectionBetween(AActor* Object1, AActor* Object2) const
{
	FVector Object1Origin;
	FVector Object1Extent;
	FVector Object2Origin;
	FVector Object2Extent;

	Object1->GetActorBounds(false, Object1Origin, Object1Extent);
	Object2->GetActorBounds(false, Object2Origin, Object2Extent);

	double X1min = Object1Origin.X - Object1Extent.X;
	double X1max = Object1Origin.X + Object1Extent.X;
	double Y1min = Object1Origin.Y - Object1Extent.Y;
	double Y1max = Object1Origin.Y + Object1Extent.Y;
	double Z1min = Object1Origin.Z - Object1Extent.Z;
	double Z1max = Object1Origin.Z + Object1Extent.Z;

	double X2min = Object2Origin.X - Object2Extent.X;
	double X2max = Object2Origin.X + Object2Extent.X;
	double Y2min = Object2Origin.Y - Object2Extent.Y;
	double Y2max = Object2Origin.Y + Object2Extent.Y;
	double Z2min = Object2Origin.Z - Object2Extent.Z;
	double Z2max = Object2Origin.Z + Object2Extent.Z;

	if (X1min <= X2max && X1max >= X2min &&
		Y1min <= Y2max && Y1max >= Y2min &&
		Z1min <= Z2max && Z1max >= Z2min)
	{
		return true;
	}
	return false;
}
