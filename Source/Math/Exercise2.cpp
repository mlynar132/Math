#include "Exercise2.h"

AExercise2::AExercise2()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);
}

void AExercise2::BeginPlay()
{
	Super::BeginPlay();
}

void AExercise2::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	FName PropertyName = (PropertyChangedEvent.Property != NULL)
		                     ? PropertyChangedEvent.Property->GetFName()
		                     : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AExercise2, T))
	{
		MyTransformInterpolation();
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void AExercise2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//I'm not clamping T bettwen 0 and 1 cuz the other values are also valid resaults
void AExercise2::MyTransformInterpolation()
{
	FVector t1 = InterpolationObject1->GetActorLocation();
	FVector t2 = InterpolationObject2->GetActorLocation();	

	SetActorLocation(FVector(t1.X + T * (t2.X - t1.X),
	                         t1.Y + T * (t2.Y - t1.Y),
	                         t1.Z + T * (t2.Z - t1.Z)));
}
