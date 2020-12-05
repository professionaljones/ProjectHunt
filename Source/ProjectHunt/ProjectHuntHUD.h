// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "ProjectHunt/ProjectHunt.h"
#include "GameFramework/HUD.h"
#include "ProjectHuntHUD.generated.h"

UCLASS()
class AProjectHuntHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectHuntHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "HUD|Settings")
		bool bShowCrosshair = false;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

