// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment7GameMode.h"
#include "Assignment7Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment7GameMode::AAssignment7GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
