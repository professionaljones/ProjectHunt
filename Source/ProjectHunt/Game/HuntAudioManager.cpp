// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntAudioManager.h"
#include "Components/AudioComponent.h"

// Sets default values
AHuntAudioManager::AHuntAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyAudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");

}

// Called when the game starts or when spawned
void AHuntAudioManager::BeginPlay()
{
	Super::BeginPlay();
	//PlayNextTrack();
}

// Called every frame
void AHuntAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHuntAudioManager::PlayNextTrack(USoundBase* NewTrack)
{
	if (NewTrack)
	{
		CurrentTrack = NewTrack;
	}
	if (!NewTrack)
	{
		CurrentTrack = SaveRoomTrack.Get();
	}
	MyAudioComponent->SetSound(CurrentTrack);
	MyAudioComponent->Play(0.0f);
}

