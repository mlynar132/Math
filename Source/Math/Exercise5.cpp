// Fill out your copyright notice in the Description page of Project Settings.


#include "Exercise5.h"

AExercise5::AExercise5()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);
}

void AExercise5::BeginPlay()
{
	Super::BeginPlay();
}

void AExercise5::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL)
		                     ? PropertyChangedEvent.Property->GetFName()
		                     : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AExercise5, T) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AExercise5, NoiseStrength))
	{
		MyTransformInterpolation();
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AExercise5::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//I'm not clamping T bettwen 0 and 1 cuz the other values are also valid resaults
void AExercise5::MyTransformInterpolation()
{
	FVector t1 = InterpolationObject1->GetActorLocation();
	FVector t2 = InterpolationObject2->GetActorLocation();

	SetActorLocation(FVector(
		t1.X + T * (t2.X - t1.X) + rand() % static_cast<int>(NoiseStrength + 1) * (rand() % 2 - 1),
		t1.Y + T * (t2.Y - t1.Y) + rand() % static_cast<int>(NoiseStrength + 1) * (rand() % 2 - 1),
		t1.Z + T * (t2.Z - t1.Z) + rand() % static_cast<int>(NoiseStrength + 1) * (rand() % 2 - 1)));
}
