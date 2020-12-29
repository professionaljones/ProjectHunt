// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntStatsComponent.h"
#include "ProjectHunt/ProjectHuntCharacter.h"

// Sets default values for this component's properties
UHuntStatsComponent::UHuntStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bEditableWhenInherited = true;
	// ...

	QuicksilverStats.CurrentAbility = ESuitMainAbilities::MA_Quicksilver;
	QuicksilverStats.CurrentAbilityLevel = 1;
	QuicksilverStats.fAragonConsumptionAmount = 15.0f;
	OverloadStats.CurrentAbility = ESuitMainAbilities::MA_Overload;
	OverloadStats.CurrentAbilityLevel = 1;
	QuicksilverStats.fAragonConsumptionAmount = 18.0f;
}


// Called when the game starts
void UHuntStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	//CurrentHealth = MaxHealth;
	
}


// Called every frame
void UHuntStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


ESuitMainAbilities UHuntStatsComponent::GetCurrentPower()
{
	return CurrentSuitPower;
}

float UHuntStatsComponent::GetCurrentHealth()
{
	UI_CurrentHealth = CurrentHealth;
	return UI_CurrentHealth;
}

float UHuntStatsComponent::GetMaxHealth()
{
	UI_MaxHealth = MaxHealth;
	return UI_MaxHealth;
}

float UHuntStatsComponent::GetHealthPercentage()
{
	return CurrentHealth / MaxHealth;
}

float UHuntStatsComponent::GetCurrentAragon()
{
	UI_CurrentAragon = CurrentAragon;
	return UI_CurrentAragon;
}

float UHuntStatsComponent::GetMaxAragon()
{
	UI_MaxAragon = MaxAragon;
	return UI_MaxAragon;
}

float UHuntStatsComponent::GetAragonPercentage()
{
	return CurrentAragon / MaxAragon;
}

void UHuntStatsComponent::UpgradeHealthStats(float IncreaseAmount)
{
	MaxHealth = MaxHealth + IncreaseAmount;
	CurrentHealth = MaxHealth;
}

void UHuntStatsComponent::UpgradeAragonStats(float IncreaseAmount)
{
	MaxAragon = MaxAragon + IncreaseAmount;
	CurrentAragon = MaxAragon;
}

void UHuntStatsComponent::UpdateMaxHealth(float NewHealthAmount)
{
	MaxHealth = NewHealthAmount;
	CurrentHealth = MaxHealth;
}

void UHuntStatsComponent::UpdateMaxAragon(float NewAragonAmount)
{
	MaxAragon = NewAragonAmount;
	CurrentAragon = MaxAragon;
}

void UHuntStatsComponent::ConsumeAragon(float ConsumeAmount)
{
	CurrentAragon -= ConsumeAmount;
	if (bIsAragonEmpty)
	{
		bIsAragonEmpty = false;
	}
	if (CurrentAragon <= 0)
	{
		bIsAragonEmpty = true;
		
	}
}

void UHuntStatsComponent::ConsumeAragon_Power()
{
	if (bIsPowerActive)
	{
		switch (CurrentSuitPower)
		{
		case ESuitMainAbilities::MA_Quicksilver:
		{
			//bIsPowerActive = true;
			ConsumeAragon(QuicksilverStats.fAragonConsumptionAmount);
			if (QuicksilverStats.CurrentAbilityLevel >= 2)
			{
				RecoverHealth(8.0f);
			}
			if (QuicksilverStats.CurrentAbilityLevel >= 3)
			{
				GetOwner()->CustomTimeDilation = fActorSlowDownIgnoredValue;
			}
			break;
		}
		case ESuitMainAbilities::MA_Overload:
		{
			//bIsPowerActive = true;
			ConsumeAragon(OverloadStats.fAragonConsumptionAmount);
			break;
		}
		default:
			break;
		}
	}
	else
	{
		DeactivatePower();
	}
	
}

void UHuntStatsComponent::RechargeAragon()
{
	if (!bIsRecharging)
	{
		bIsRecharging = true;
		
	}
	if (bIsRecharging)
	{
		CurrentAragon += AragonRechargeAmount;
	}
	if (CurrentAragon >= MaxAragon)
	{
		CurrentAragon = MaxAragon;
		bIsRecharging = false;
	}
}

void UHuntStatsComponent::ModifyStandardResistance(float NewResistAmount)
{
	StandardAmmoDefense = NewResistAmount;
}

void UHuntStatsComponent::ModifyFireResistance(float NewResistAmount)
{
	FireAmmoDefense = NewResistAmount;
}

void UHuntStatsComponent::ModifyIceResistance(float NewResistAmount)
{
	IceAmmoDefense = NewResistAmount;
}

void UHuntStatsComponent::ModifyShockResistance(float NewResistAmount)
{
	ShockAmmoDefense = NewResistAmount;
}

void UHuntStatsComponent::ModifyAragonResistance(float NewResistAmount)
{
	AragonRechargeAmount = NewResistAmount;
}

void UHuntStatsComponent::ModifyExplosiveResistance(float NewResistAmount)
{

}

void UHuntStatsComponent::DamageHealth(float DecreaseAmount)
{
	CurrentHealth -= DecreaseAmount;
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		bIsDead = true;
		OnDeathDelegate.Broadcast();
	}
}

void UHuntStatsComponent::RecoverHealth(float RecoverAmount)
{
	CurrentHealth += RecoverAmount;
	if (CurrentHealth >= MaxHealth)
	{
		CurrentHealth = MaxHealth;
		
	}

}

void UHuntStatsComponent::InitStats()
{
	CurrentHealth = MaxHealth;

	if (MaxAragon != 0)
	{
		CurrentAragon = MaxAragon;
	}
}

void UHuntStatsComponent::ActivatePower()
{
	AProjectHuntCharacter* localCharacter = Cast<AProjectHuntCharacter>(GetOwner());
	if (!bIsAragonEmpty && !bIsDead)
	{
		//bIsPowerActive = !bIsPowerActive;
		if (bIsPowerActive)
		{
			switch (CurrentSuitPower)
			{
			case ESuitMainAbilities::MA_Quicksilver:
			{
				UGameplayStatics::SetGlobalTimeDilation(GetWorld(), fSlowDownValue);
				GetOwner()->CustomTimeDilation = fSlowDownValue;
				break;
				//ConsumeAragon(QuicksilverStats.fAragonConsumptionAmount);
				
			}
			case ESuitMainAbilities::MA_Showstopper:
			{
				if (localCharacter->GetClass()->ImplementsInterface(UHuntPlayerInterface::StaticClass()))
				{
					IHuntPlayerInterface::Execute_ActivateSuitPower(localCharacter, CurrentSuitPower);
					break;
				}
			}
			case ESuitMainAbilities::MA_Overload:
			{
				//ConsumeAragon(OverloadStats.fAragonConsumptionAmount);
				GetOwner()->CustomTimeDilation = fActorSpeedUpValue;
				break;
			}

		}
		}
	}
	
}

void UHuntStatsComponent::DeactivatePower()
{
	AProjectHuntCharacter* localCharacter = Cast<AProjectHuntCharacter>(GetOwner());
	bIsPowerActive = false;

	if (CurrentAragon < MaxAragon || bIsAragonEmpty)
	{
		bIsRecharging = true;
		//RechargeAragon();
	}

	switch (CurrentSuitPower)
	{
	case ESuitMainAbilities::MA_Quicksilver:
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		GetOwner()->CustomTimeDilation = 1.0f;
		break;
	}
	case ESuitMainAbilities::MA_Showstopper:
	{
		if (localCharacter->GetClass()->ImplementsInterface(UHuntPlayerInterface::StaticClass()))
		{
			IHuntPlayerInterface::Execute_DeactivateSuitPower(localCharacter, CurrentSuitPower);
			break;
		}
	}
	case ESuitMainAbilities::MA_Overload:
	{
		GetOwner()->CustomTimeDilation = 1.0f;
		break;
	}
	}
}

