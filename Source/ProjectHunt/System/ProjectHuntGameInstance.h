// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HuntSaveGame.h"
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

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	//	class AHuntPlayerCharacter* PlayerReference;

	////Use this function to seemlessly save data, ideally for auto saves
	//UFUNCTION(BlueprintCallable, Category = "Save/Load")
	//	void AsyncSaveGame();

	////Use this function to save data, ideally for menu saves
	//UFUNCTION(BlueprintCallable, Category = "Save/Load")
	//	void SyncSaveGame();

	//UFUNCTION(BlueprintCallable, Category = "Save/Load")
	//	void SavePlayerData();
	//
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save Data")
	//class UHuntSaveGame* SaveGameInstance;

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
