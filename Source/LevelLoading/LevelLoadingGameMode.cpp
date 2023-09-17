// Copyright Epic Games, Inc. All Rights Reserved.

#include "LevelLoadingGameMode.h"
#include "LevelLoadingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALevelLoadingGameMode::ALevelLoadingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
