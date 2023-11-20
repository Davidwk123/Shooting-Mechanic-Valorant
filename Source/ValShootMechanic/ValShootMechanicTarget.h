// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValShootMechanicTarget.generated.h"

UCLASS()
class VALSHOOTMECHANIC_API AValShootMechanicTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AValShootMechanicTarget();

	/** Dummy mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Code for when something overlaps this component */
	UFUNCTION()
	void OverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

};
