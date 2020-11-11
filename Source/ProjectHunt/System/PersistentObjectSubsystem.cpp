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
		}
	}
	else
	{
		//If not, ignore it.
	}
}
