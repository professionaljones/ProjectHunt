// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntGameInstanceUGC.h"

UHuntGameInstanceUGC::UHuntGameInstanceUGC()
{
	RecordingName = "MyReplay";
	friendlyRecordingName = "My Replay";
}

void UHuntGameInstanceUGC::Init()
{
	// Instantiate the registry and find mod packages
	UGCRegistry = NewObject<UUGCRegistry>(this);
	UGCRegistry->FindUGCPackages();
	Super::Init();
}

void UHuntGameInstanceUGC::StartRecording()
{
	StartRecordingReplay(RecordingName, friendlyRecordingName);
}

void UHuntGameInstanceUGC::StopRecording()
{
	StopRecordingReplay();
}

void UHuntGameInstanceUGC::StartReplay()
{
	PlayReplay(RecordingName, nullptr);
}