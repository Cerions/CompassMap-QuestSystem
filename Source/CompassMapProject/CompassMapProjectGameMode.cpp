// Copyright Epic Games, Inc. All Rights Reserved.

#include "CompassMapProjectGameMode.h"
#include "CompassMapProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACompassMapProjectGameMode::ACompassMapProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
