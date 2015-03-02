// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Intensiivi.h"
#include "IntensiiviGameMode.h"
#include "IntensiiviPlayerController.h"
#include "IntensiiviCharacter.h"

AIntensiiviGameMode::AIntensiiviGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = AIntensiiviPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}