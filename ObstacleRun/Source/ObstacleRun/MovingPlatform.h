// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLERUN_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Add the velocity variable for platform to move 200cm/s (NOT per frame)
	UPROPERTY(EditAnywhere, Category = "Moving Platform") // add UPROPETRY() for it to show on the UE editor
	FVector PlatformVelocity = FVector(0, 0, 200);
	UPROPERTY(EditAnywhere, Category = "Rotation Platform") 
	FRotator RotationVelocity; // Add the velocity variable for rotate platform

	UPROPERTY(EditAnywhere, Category = "Moving Platform")
	float LimitDistance = 500;

	FVector StartLocation; // variable store where the character's start location

	void MovePlatform(float DeltaTime);
	void RotatePlatform(float DeltaTime);
	bool ShouldPlatformReverse() const;
	float GetDistanceMoved() const;

};
