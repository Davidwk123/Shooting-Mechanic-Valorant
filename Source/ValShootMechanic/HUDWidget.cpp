// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"

// The "define" allows the use of the "LOCTEXT" in the functions, which allow int values to be used with string values 
#define LOCTEXT_NAMESPACE "UMG"
void UHUDWidget::SetCurrentDistance(int Distance)
{
	if (CurrentDistance)
	{
		CurrentDistance->SetText(FText::Format(LOCTEXT("CombinedTextKey", "{0}m"), Distance));
	}
}

void UHUDWidget::SetWeaponDropoff(bool bDidWeaponDropoff)
{
	if (WeaponDropoff)
	{
		if (bDidWeaponDropoff)
		{
			WeaponDropoff->SetText(FText::FromString("(Damage Droppoff applied)"));
		}
		else
		{
			WeaponDropoff->SetText(FText::FromString("(Regular Damage)"));
		}
		
	}
}

void UHUDWidget::SetBodyLocationDamage(FText BodyLocation, int Damage)
{
	BodyLocationDamage->SetText(FText::Join(BodyLocation, FText::Format(LOCTEXT("CombinedTextKey", ": {0} Damage"), Damage)));
}

#undef LOCTEXT_NAMESPACE
