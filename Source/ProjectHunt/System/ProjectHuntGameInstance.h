// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectHunt/Character/Player/HuntPlayerCharacter.h"
#include "ProjectHuntGameInstance.generated.h"


/**
 *
 */
UCLASS()
class PROJECTHUNT_API UProjectHuntGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UProjectHuntGameInstance();


	//Name for the recorded replay
	UPROPERTY(EditDefaultsOnly, Category = "Replays")
		FString RecordingName;

	//Name for the recorded replay for UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replays")
		FString friendlyRecordingName;

	UFUNCTION(BlueprintCallable, Category = "Replays")
		void StartRecording();

	UFUNCTION(BlueprintCallable, Category = "Replays")
		void StopRecording();

	UFUNCTION(BlueprintCallable, Category = "Replays")
		void StartReplay();

};
