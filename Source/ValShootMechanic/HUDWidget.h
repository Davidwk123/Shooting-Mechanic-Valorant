// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class VALSHOOTMECHANIC_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Textblock to display distance between characters */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CurrentDistance;

	/** Textblock to display if damage dropoff is applied */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* WeaponDropoff;

	/** Textblock to display where the user shot the character and the damage it did */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BodyLocationDamage;

	/*
	* Setter functions to allow updates to the textblocks in the HUD
	*/
	UFUNCTION()
	void SetCurrentDistance(int Distance);

	UFUNCTION()
	void SetWeaponDropoff(bool bDidWeaponDropoff);

	UFUNCTION()
	void SetBodyLocationDamage(FText BodyLocation, int Damage);
	
};
