// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "ProjectHunt/ProjectHunt.h"
#include "UGCBaseGameInstance.h"
#include "ProjectHunt/Character/Player/HuntPlayerCharacter.h"
#include "HuntGameInstanceUGC.generated.h"

/**
 *
 */
UCLASS()
class PROJECTHUNT_API UHuntGameInstanceUGC : public UUGCBaseGameInstance
{
	GENERATED_BODY()

public:
	UHuntGameInstanceUGC();

	virtual void Init() override;

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
