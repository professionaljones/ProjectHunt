// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectHuntGameMode.h"
#include "ProjectHuntHUD.h"
#include "ProjectHuntCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectHuntGameMode::AProjectHuntGameMode()
	: Super()
{
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Blueprints/Player/BP_FP_TrishPlayerCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProjectHuntHUD::StaticClass();
}
