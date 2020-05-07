// Fill out your copyright notice in the Description page of Project Settings.

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

};
