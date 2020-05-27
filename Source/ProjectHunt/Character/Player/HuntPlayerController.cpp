// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntPlayerController.h"


AHuntPlayerController::AHuntPlayerController()
{

}

float AHuntPlayerController::GetLookXSensitivity_PC()
{
	return LookXSensitivity_PC;
}

float AHuntPlayerController::GetLookYSensitivity_PC()
{
	return LookYSensitivity_PC;
}

float AHuntPlayerController::GetLookXSensitivity_Gamepad()
{
	return LookXSensitivity_GP;
}

float AHuntPlayerController::GetLookYSensitivity_Gamepad()
{
	return LookYSensitivity_GP;
}

void AHuntPlayerController::RestartReplayRecording()
{
	DemoDriver = GetWorld()->DemoNetDriver;
	DemoDriver->GotoTimeInSeconds(0.0f);

}


void AHuntPlayerController::SeekReplayRecording(float NewPosition)
{
	DemoDriver = GetWorld()->DemoNetDriver;
	DemoDriver->GotoTimeInSeconds(NewPosition);

}

float AHuntPlayerController::GetReplayPlaybackPosition()
{
	DemoDriver = GetWorld()->DemoNetDriver;
	return DemoDriver->GetDemoCurrentTime();
}

float AHuntPlayerController::GetReplayPlaybackLength()
{
	DemoDriver = GetWorld()->DemoNetDriver;
	return DemoDriver->GetDemoTotalTime();
}


