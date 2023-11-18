// Fill out your copyright notice in the Description page of Project Settings.


#include "ValShootMechanicDummy.h"
#include "Components/SphereComponent.h"
#include "ValShootMechanicCharacter.h"

// Sets default values
AValShootMechanicDummy::AValShootMechanicDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Mesh component
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("DummyMesh"));
	RootComponent = Mesh;

	// Create TriggerSpehre component
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetupAttachment(RootComponent);
	// Weapon drop off for the Ghost happens at 30m
	TriggerSphere->InitSphereRadius(3000.f);

}

// Called when the game starts or when spawned
void AValShootMechanicDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AValShootMechanicDummy::OverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checking if it is a First Person Character overlapping
	AValShootMechanicCharacter* Character = Cast<AValShootMechanicCharacter>(OtherActor);
	if (Character)
	{

	}
}

void AValShootMechanicDummy::OverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checking if it is a First Person Character overlapping
	AValShootMechanicCharacter* Character = Cast<AValShootMechanicCharacter>(OtherActor);
	if (Character)
	{

	}
}

