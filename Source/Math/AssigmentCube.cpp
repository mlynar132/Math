// Fill out your copyright notice in the Description page of Project Settings.


#include "AssigmentCube.h"

#include "Components/TextRenderComponent.h"

// Sets default values
AAssigmentCube::AAssigmentCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);

	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetupAttachment(MeshComponent);
}

bool AAssigmentCube::ShouldTickIfViewportsOnly() const
{
	if (Target == nullptr)
	{
		Text->SetText(FText::FromString("No Target"));
		return Super::ShouldTickIfViewportsOnly();
	}
	
	FString TextTemp;

	FTransform Transform = GetTransform();
	FTransform TargetTransform = Target->GetTransform();

	Transform.GetRotation().GetForwardVector();
	Transform.GetRotation().GetRightVector();
	
	if (TargetTransform.GetLocation().Z > Transform.GetLocation().Z )
	{
		TextTemp.Append("Above");
		// Ehehehe |= EMyEnum::Above;
		// if (Ehehehe & EMyEnum::Above)
		// {
		// 	UE_LOG(LogTemp,Warning,TEXT("ASDFS"));	
		// }
	}
	else if (TargetTransform.GetLocation().Z == Transform.GetLocation().Z )
	{
		TextTemp.Append("Same height");
	}
	else
	{
		TextTemp.Append("Bellow");
	}
	if (TargetTransform.GetLocation().X > Transform.GetLocation().X )
	{
		TextTemp.Append(", In front");
	}
	else if (TargetTransform.GetLocation().X == Transform.GetLocation().X )
	{
		TextTemp.Append(", Same X");
	}
	else
	{
		TextTemp.Append(", behind");
	}
	if (TargetTransform.GetLocation().Y > Transform.GetLocation().Y )
	{
		TextTemp.Append(", on the right");
	}
	else if (TargetTransform.GetLocation().Y == Transform.GetLocation().Y )
	{
		TextTemp.Append(", Same y");
	}
	else
	{
		TextTemp.Append(", on the left");
	}
	Text->SetText(FText::FromString(TextTemp));
	return Super::ShouldTickIfViewportsOnly();
}

// Called when the game starts or when spawned
void AAssigmentCube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAssigmentCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}