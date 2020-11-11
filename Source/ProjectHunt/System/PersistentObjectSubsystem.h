// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PersistentObjectSubsystem.generated.h"


//This subsystem will replace the Persistent Object Manager from Mathew Wadstein: https://youtu.be/YrdEha-Ogc8
/*Each valid object will register itself to the subsystem on BeginPlay
Then we will communicate as normal with the previous system*/

/**
 * 
 */
UCLASS()
class PROJECTHUNT_API UPersistentObjectSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Object Registration")
		void RegisterSaveableObject(class AActor* NewSaveableObject);

	UPROPERTY(BlueprintReadOnly, Category = "Saveable Objects")
		TArray<class AActor*> AllSaveableObjects;
private:

	
	
};
