// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "ProjectHunt/ProjectHunt.h"
#include "UObject/Interface.h"
#include "HuntGameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHuntGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class PROJECTHUNT_API IHuntGameInstanceInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
		void OnAsyncSave(FString SaveSlotName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
		void OnAsyncLoad(FString SaveSlotToLoadName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
		void OnAsyncSaveProfile(FString ProfileSlotName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
		void OnAsyncLoadProfile(FString ProfileSlotToLoadName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
		void OnMenuSave(FString SaveSlotName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
		void OnMenuLoad(FString SaveSlotToLoadName);*/

	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Event Response|Data")
	//	FString IsThisSaveRecent(FString SaveSlotName);
};
