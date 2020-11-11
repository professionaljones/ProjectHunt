// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "PersistentObjectSubsystem.h"
#include "ProjectHunt/Interfaces/Game/HuntSaveableObjectInterface.h"

void UPersistentObjectSubsystem::RegisterSaveableObject(class AActor* NewSaveableObject)
{
	if (NewSaveableObject)
	{
		//If the object implements the saveable interface, add it to the array of saveable objects
		if(NewSaveableObject->GetClass()->ImplementsInterface(UHuntSaveableObjectInterface::StaticClass()))
		{
			//Register object to array
			AllSaveableObjects.Add(NewSaveableObject);
			//UE_LOG(LogTemp, Log, TEXT("Object successfully registered - %s") + NewSaveablObject->GetName()));
			UE_LOG(LogTemp, Log, TEXT("Persistent Object Manager - The object: %s Has been successfully registered"), *NewSaveableObject->GetName());
		}
	}
	else
	{
		//If not, ignore it.
	}
}

void UPersistentObjectSubsystem::CheckSaveSlotStatus()
{
	//if()
}
