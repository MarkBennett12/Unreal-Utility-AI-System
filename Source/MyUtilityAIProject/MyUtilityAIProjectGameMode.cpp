// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUtilityAIProjectGameMode.h"
#include "MyUtilityAIProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyUtilityAIProjectGameMode::AMyUtilityAIProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
