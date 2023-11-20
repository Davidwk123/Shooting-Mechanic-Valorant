// Fill out your copyright notice in the Description page of Project Settings.


#include "ValShootMechanicTarget.h"
#include "ValShootMechanicCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AValShootMechanicTarget::AValShootMechanicTarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Mesh component
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DummyMesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AValShootMechanicTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

void AValShootMechanicTarget::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checking if it is a First Person Character is overlapping
	AValShootMechanicCharacter* Character = Cast<AValShootMechanicCharacter>(OtherActor);
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), Character);
	}
}

void AValShootMechanicTarget::OverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checking if it is a First Person Character overlapping
	AValShootMechanicCharacter* Character = Cast<AValShootMechanicCharacter>(OtherActor);
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), Character);
	}
}


