// Fill out your copyright notice in the Description page of Project Settings.


#include "Exercise4.h"

AExercise4::AExercise4()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AExercise4::BeginPlay()
{
	CollisionTimer.Empty();
	Directions.Empty();
	Velocities.Empty();
	for (auto MyObject : Objects)
	{
		CollisionTimer.Add(0.0f);
		Directions.Add(/*FVector::ForwardVector*/ RandomDirectionInSphere());
		Velocities.Add(/*5*/ rand() % 6);
	}
	Super::BeginPlay();
}

void AExercise4::Tick(float DeltaTime)
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), ArenaRadius, 32, FColor::Orange, false, -1, 0, 10);

	//collision marking
	TArray<bool> IsIntersecting;
	for (int i = 0; i < Objects.Num(); i++)
	{
		IsIntersecting.Push(false);
		CollisionTimer[i] -= DeltaTime;
	}

	//detect collision
	for (int i = 0; i < Objects.Num() - 1; i++)
	{
		for (int j = i + 1; j < Objects.Num(); j++)
		{
			if (CheckForInterSectionBetween(Objects[i], Objects[j]))
			{
				Directions[i] = Bounce(i, j);
				Directions[j] = Bounce(j, i);
				Objects[i]->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, IntersectionsMaterial);
				Objects[j]->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, IntersectionsMaterial);
				IsIntersecting[i] = true;
				IsIntersecting[j] = true;
			}
		}
	}
	//Collision colloring
	for (int i = 0; i < Objects.Num(); i++)
	{
		if (IsIntersecting[i])
		{
			CollisionTimer[i] = 1.0f;
			Objects[i]->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, IntersectionsMaterial);
		}
		else if (CollisionTimer[i] <= 0.0f)
		{
			Objects[i]->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, NoIntersectionsMaterial);
		}
	}

	//Catch Balls Outside Arena
	for (int i = 0; i < Objects.Num(); i++)
	{
		FVector ObjectOrigin;
		FVector ObjectExtent;

		Objects[i]->GetActorBounds(false, ObjectOrigin, ObjectExtent);
		float ObjectRadius = ObjectExtent.X;

		if (FVector::Distance(ObjectOrigin, GetActorLocation()) >= ArenaRadius - ObjectRadius)
		{
			Directions[i] = BounceFromWall(i);
			// Directions[i] = (GetActorLocation() - ObjectOrigin);
			// Directions[i].Normalize();
		}
	}

	//Move
	for (int i = 0; i < Objects.Num(); i++)
	{
		Objects[i]->SetActorLocation(Objects[i]->GetActorLocation() + Directions[i] * Velocities[i]);
	}

	Super::Tick(DeltaTime);
}

void AExercise4::AddObject()
{
	Objects.Add(GetWorld()->SpawnActor<AActor>(Object, GetActorLocation(), FRotator::ZeroRotator));
}

void AExercise4::RemoveObject()
{
	if (!Objects.IsEmpty())
	{
		Objects.Pop()->Destroy();
	}
}

bool AExercise4::CheckForInterSectionBetween(AActor* Object1, AActor* Object2)
{
	FVector Object1Origin;
	FVector Object1Extent;
	FVector Object2Origin;
	FVector Object2Extent;

	Object1->GetActorBounds(false, Object1Origin, Object1Extent);
	Object2->GetActorBounds(false, Object2Origin, Object2Extent);

	float Object1Radius = Object1Extent.X;
	float Object2Radius = Object2Extent.X;

	if (FVector::Distance(Object1Origin, Object2Origin) <= Object1Radius + Object2Radius)
	{
		return true;
	}
	return false;
}

FVector AExercise4::Bounce(int32 BouncingObject, int32 Surface)
{
	FVector ObjectLocation = Objects[BouncingObject]->GetActorLocation();
	FVector SurfaceLocation = Objects[Surface]->GetActorLocation();

	FVector ObjectDir = Directions[BouncingObject];

	FVector Normal = ObjectLocation - SurfaceLocation;
	Normal.Normalize();

	float Dot = FVector::DotProduct(ObjectDir, Normal);

	FVector Result = ObjectDir - 2 * Dot * Normal;

	return Result;
}

FVector AExercise4::BounceFromWall(int32 BouncingObject)
{
	FVector ObjectLocation = Objects[BouncingObject]->GetActorLocation();
	FVector ObjectDir = Directions[BouncingObject];

	FVector Normal = GetActorLocation() - ObjectLocation;
	Normal.Normalize();

	float Dot = FVector::DotProduct(ObjectDir, Normal);

	FVector Result = ObjectDir - 2 * Dot * Normal;

	return Result;
}

FVector AExercise4::RandomDirectionInSphere()
{
	double u = rand();
	double x1 = rand();
	double x2 = rand();
	double x3 = rand();

	double mag = sqrt(x1 * x1 + x2 * x2 + x3 * x3);
	x1 /= mag;
	x2 /= mag;
	x3 /= mag;

	double c = cbrt(u);

	FVector Result = FVector(x1 * c, x2 * c, x3 * c);
	Result.Normalize();

	return Result;
}
