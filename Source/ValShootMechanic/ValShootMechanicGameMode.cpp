// Copyright Epic Games, Inc. All Rights Reserved.

#include "ValShootMechanicGameMode.h"
#include "ValShootMechanicCharacter.h"
#include "UObject/ConstructorHelpers.h"

AValShootMechanicGameMode::AValShootMechanicGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
