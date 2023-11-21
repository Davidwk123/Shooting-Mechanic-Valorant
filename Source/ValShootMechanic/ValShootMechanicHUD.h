// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDWidget.h"
#include "ValShootMechanicHUD.generated.h"

/**
 * 
 */
UCLASS()
class VALSHOOTMECHANIC_API AValShootMechanicHUD : public AHUD
{
	GENERATED_BODY()

public:
	AValShootMechanicHUD();

	UHUDWidget* GetHUDWidget();

protected:
	// Used to add new Widget from Blueprint
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UHUDWidget> HUDWidgetClass;

	virtual void BeginPlay() override;

	// This function runs before BeginPlay() and the other Actors, this will allow the HUDWidget to be intialized first so that it can be refrenced by other Actors
	virtual void PostInitializeComponents() override;

private:
	// Stores new Widget from HUDWidgetClass
	class UHUDWidget* HUDWidget;
};
