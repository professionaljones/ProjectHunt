// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioManagerSubsystem.generated.h"

class AHuntAudioManager;

/**
 * 
 */
UCLASS()
class PROJECTHUNT_API UAudioManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	//// Begin USubsystem
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	//virtual void Deinitialize() override;
	//// End USubsystem

	UFUNCTION(BlueprintCallable, Category = "My Subsystems|Audio")
	void SetNewAudioManager(AHuntAudioManager* NewAudioManager);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = Audio)
	AHuntAudioManager* GetAudioManager();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Audio)
		class AHuntAudioManager* CurrentAudioManager;

private:
	
	
	
};
