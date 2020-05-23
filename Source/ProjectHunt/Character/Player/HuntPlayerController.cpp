// Fill out your copyright notice in the Description page of Project Settings.


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
