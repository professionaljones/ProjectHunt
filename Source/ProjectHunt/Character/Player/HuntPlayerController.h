// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HuntPlayerController.generated.h"

/**
 *
 */
UCLASS()
class PROJECTHUNT_API AHuntPlayerController : public APlayerController
{
	GENERATED_BODY()

	AHuntPlayerController();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float LookXSensitivity_PC = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float LookYSensitivity_PC = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float LookXSensitivity_GP = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float LookYSensitivity_GP = 0.5f;

	UFUNCTION(BlueprintCallable, Category = "Camera")
		float GetLookXSensitivity_PC();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		float GetLookYSensitivity_PC();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		float GetLookXSensitivity_Gamepad();

	UFUNCTION(BlueprintCallable, Category = "Camera")
		float GetLookYSensitivity_Gamepad();

protected:

	/*UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "cheats")
	class UWidgetBlueprint* ConsoleWBP;*/



};
