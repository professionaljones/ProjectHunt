// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "ScannableActorComponent.generated.h"

/* This struct serves as a way to maintain the info about actor's info for the player's Logbook*/

USTRUCT(BlueprintType)
struct FActorLogbookData : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logbook")
		//The Ability in question
		FName ActorName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logbook")
		//The first part of the Actor's description (Must always be filled)
		FString DescriptionPart1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logbook")
		//The first part of the Actor's description 
		FString DescriptionPart2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logbook")
		//The first part of the Actor's description 
		FString DescriptionPart3;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTHUNT_API UScannableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UScannableActorComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logbook")
		bool bWasScanned = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Logbook")
		FActorLogbookData ActorLogbook;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
