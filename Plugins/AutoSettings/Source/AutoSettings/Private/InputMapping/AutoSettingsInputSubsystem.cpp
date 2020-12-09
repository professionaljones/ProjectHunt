// Copyright Sam Bonifacio. All Rights Reserved.


#include "InputMapping/AutoSettingsInputSubsystem.h"
#include "Misc/AutoSettingsConfig.h"
#include "InputMapping/InputMappingManager.h"
#include "Engine/GameInstance.h"
#include "Engine/LocalPlayer.h"

void UAutoSettingsInputSubsystem::Tick(float DeltaTime)
{
	if (GetDefault<UAutoSettingsConfig>()->bAutoInitializePlayerInputOverrides)
	{
		// Polling this is a bit dirty, but can't find any engine events that fire when players are added so it'll have to do

		UGameInstance* GameInstance = GetGameInstance();
		if (GameInstance)
		{
			TArray<ULocalPlayer*> Players = GameInstance->GetLocalPlayers();
			for (ULocalPlayer* Player : Players)
			{
				if (APlayerController* PlayerController = Player->GetPlayerController(GetWorld()))
				{
					if (PlayerController->PlayerInput && !UInputMappingManager::Get()->IsPlayerControllerRegistered(PlayerController))
					{
						UInputMappingManager::InitializePlayerInputOverridesStatic(PlayerController);
					}
				}
			}
		}
		
	}
}
