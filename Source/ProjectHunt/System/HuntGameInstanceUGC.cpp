// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntGameInstanceUGC.h"

UHuntGameInstanceUGC::UHuntGameInstanceUGC()
{
	RecordingName = "MyReplay";
	friendlyRecordingName = "My Replay";
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