// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// start location is where the charactor at
	StartLocation = GetActorLocation();

	FString ActorName = GetName();

	UE_LOG(LogTemp, Display, TEXT("Begin play: %s"), *ActorName);
}

// Game Loop called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}
//-----------------------------------------------------------------------------
// Platform move forwards or backwards
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// platform move at intend direction
	if (ShouldPlatformReverse() == false)
	{
		// Get current location of Actor
		FVector CurrentLocation = GetActorLocation();
		// add vector to that location
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime); // multiply platform velocity with DeltaTime, so the actor become independent from frame rate
		// Set the location of Actor
		SetActorLocation(CurrentLocation);
	}
	// Reverse direction of motion if it gone too far
	else
	{
		// get normal velocity so actors are not drift
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// reset the start location by set startLocation = the end, and make sure to not over shoot when reset
		StartLocation = StartLocation + (MoveDirection * LimitDistance);
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity; // set its velocity to negative to move the opposite direction
	}
}

// Platform rotate
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation = CurrentRotation + (RotationVelocity * DeltaTime);
	SetActorRotation(CurrentRotation);
}

// Reverse direction of motion if it gone too far
bool AMovingPlatform::ShouldPlatformReverse() const
{
	// get and display travel distance of platforms
	UPROPERTY(VisibleAnywhere)
	float TraveledDistance = GetDistanceMoved();

	return TraveledDistance > LimitDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartLocation, GetActorLocation());
}
