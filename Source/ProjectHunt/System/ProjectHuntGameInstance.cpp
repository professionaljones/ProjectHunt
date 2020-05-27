// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "ProjectHuntGameInstance.h"

UProjectHuntGameInstance::UProjectHuntGameInstance()
{
	RecordingName = "MyReplay";
	friendlyRecordingName = "My Replay";
}

void UProjectHuntGameInstance::StartRecording()
{
	StartRecordingReplay(RecordingName, friendlyRecordingName);
}

void UProjectHuntGameInstance::StopRecording()
{
	StopRecordingReplay();
}

void UProjectHuntGameInstance::StartReplay()
{
	PlayReplay(RecordingName, nullptr);
}

