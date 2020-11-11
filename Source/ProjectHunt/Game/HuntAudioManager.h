// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HuntAudioManager.generated.h"

class UAudioComponent;

UCLASS()
class PROJECTHUNT_API AHuntAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHuntAudioManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio, meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* MyAudioComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Preset Tracks")
	TSoftObjectPtr<USoundBase> SaveRoomTrack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Preset Tracks")
		TSoftObjectPtr<USoundBase> GameOverTrack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Current Track")
		class USoundBase* CurrentTrack;

	UFUNCTION(BlueprintCallable, Category = "Audio|Manager Playback")
	void PlayNextTrack(USoundBase* NewTrack);

	/*USoundBase* GetLazyLoadedSound()
	{
		if (CurrentTrack.IsPending())
		{
			const FSoftObjectPath& AssetRef = CurrentTrack.ToStringReference();
			CurrentTrack = Cast<USoundBase>(Streamable.SynchronousLoad(AssetRef));
		}
		return CurrentTrack.Get();
	}*/



};
