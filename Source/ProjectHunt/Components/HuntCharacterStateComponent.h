// Copyright 2020 Brandon Jones. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HuntCharacterStateComponent.generated.h"

//What kind of projectile does this weapon use
UENUM(BlueprintType)
enum ECharacterState
{
	CS_None,
	CS_Patroling,
	CS_NeedHelp,
	CS_Supporting,
	CS_Attacking,
	CS_Defending,
	CS_Healing,
	CS_Retreating,
	CS_DevilTrigger,
	MAX_CHARACTERSTATE
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTHUNT_API UHuntCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHuntCharacterStateComponent();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = State)
	TEnumAsByte<ECharacterState> currentState = CS_Patroling;

	UFUNCTION(BlueprintCallable, Category = State)
	void SetNewState(TEnumAsByte<ECharacterState> newState);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
