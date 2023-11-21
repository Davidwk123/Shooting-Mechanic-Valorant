// Fill out your copyright notice in the Description page of Project Settings.


#include "ValShootMechanicHUD.h"
#include "HUDWidget.h"

AValShootMechanicHUD::AValShootMechanicHUD()
{
	SetActorTickEnabled(false);

	HUDWidgetClass = nullptr;
	HUDWidget = nullptr;
}

UHUDWidget* AValShootMechanicHUD::GetHUDWidget()
{
	return HUDWidget;
}

void AValShootMechanicHUD::BeginPlay()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AValShootMechanicHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// Creates new Widget from HUDWidgetClass
	if (HUDWidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
}

