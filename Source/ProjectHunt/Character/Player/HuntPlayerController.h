// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DemoNetDriver.h"
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

	UFUNCTION(BlueprintCallable, Category = "Replays")
		void RestartReplayRecording();

	UFUNCTION(BlueprintCallable, Category = "Replays")
		void SeekReplayRecording(float NewPosition);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Replays")
		float GetReplayPlaybackPosition();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Replays")
		float GetReplayPlaybackLength();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		float CurrentItemPercentage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
		float MaxItemPercentage = 1.0f;

	UDemoNetDriver* DemoDriver;

protected:

	/*UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "cheats")
	class UWidgetBlueprint* ConsoleWBP;*/

	


};
