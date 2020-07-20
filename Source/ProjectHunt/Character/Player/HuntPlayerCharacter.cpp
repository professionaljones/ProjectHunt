// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"

AHuntPlayerCharacter::AHuntPlayerCharacter()
{
	StatsComponent->MaxHealth = 200;
	StatsComponent->MaxAragon = 200;
	StatsComponent->CurrentHealth = StatsComponent->MaxHealth;
	StatsComponent->CurrentAragon = StatsComponent->MaxAragon;
	StatsComponent->AragonRechargeAmount = 15.0f;
	MaxStyleAmount = SSS_StyleLimit;

	//Create a secondary AudioComponent 
	SuitAudioComponent = CreateDefaultSubobject<UAudioComponent>("SuitAudioComponent");
}

int32 AHuntPlayerCharacter::GetJumpCount()
{
	return JumpCount;
}

int32 AHuntPlayerCharacter::GetDashCount()
{
	return DashCount;
}

bool AHuntPlayerCharacter::CanPlayerUseMissiles()
{
	return bHasMissileLauncher;
}

void AHuntPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AHuntPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AHuntPlayerCharacter::UnlockAbility(bool bUnlockAbility)
{
	bUnlockAbility = true;
}

int32 AHuntPlayerCharacter::GetCurrentMissiles()
{
	UI_CurrentMissileCount = CurrentMissileCount;
	return UI_CurrentMissileCount;
}

int32 AHuntPlayerCharacter::GetMaxMissiles()
{
	UI_MaxMissileCount = MaxMissileCount;
	return UI_MaxMissileCount;
}

void AHuntPlayerCharacter::ConsumeMissiles(int32 ConsumeMissileAmount)
{
	if (bHasMissileLauncher)
	{
		if (!bAreMissilesEmpty)
		{
			CurrentMissileCount -= ConsumeMissileAmount;
			if (CurrentMissileCount <= 0)
			{
				bAreMissilesEmpty = true;
				CurrentMissileCount = 0;
			}
		}
	}

	
}

void AHuntPlayerCharacter::RecoverMissiles(int32 RecoverAmount)
{
	CurrentMissileCount += RecoverAmount;
	if (bAreMissilesEmpty == false)
	{
		bAreMissilesEmpty = false;
	}
	if (CurrentMissileCount >= MaxMissileCount)
	{
		CurrentMissileCount = MaxMissileCount;
		
	}
}

void AHuntPlayerCharacter::UpgradeMissileCapacity(int32 IncreaseAmount)
{
	MaxMissileCount = MaxMissileCount + IncreaseAmount;
	CurrentMissileCount = MaxMissileCount;
}

float AHuntPlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (DamageAmount > 0.0f)
	{
		if (this->CanBeDamaged())
		{
			//StatsComponent->CurrentHealth -= (DamageAmount * DamageTakenModifier);
			StatsComponent->DamageHealth(DamageAmount * DamageTakenModifier);
			DecreaseStyle();
			/*switch (EPlayerSuit)
			{
			case EPlayerSuit::Suit_Standard:
				break;
			case EPlayerSuit::Suit_Version2:
				DamageTakenModifier = DamageTakenModifier - 0.15f;
				break;
			case EPlayerSuit::Suit_Version3:
				DamageTakenModifier = DamageTakenModifier - 0.30f;
				break;
			case EPlayerSuit::Suit_Version4:
				DamageTakenModifier = DamageTakenModifier - 0.50f;
				break;
			}*/
		}

		if (DamageSounds.Num() != 0)
		{
			int RandomDamageSoundIndex = UKismetMathLibrary::RandomIntegerInRange(0, DamageSounds.Num());
			if (DamageSounds.IsValidIndex(RandomDamageSoundIndex))
			{
				CharacterAudioComponent->SetSound(DamageSounds[RandomDamageSoundIndex]);
				CharacterAudioComponent->Play();
			}

		}
		if (StatsComponent->bIsDead)
		{
			if (DeathSounds.Num() != 0)
			{
				int RandomDeathSoundIndex = UKismetMathLibrary::RandomIntegerInRange(0, DeathSounds.Num());
				if (DeathSounds.IsValidIndex(RandomDeathSoundIndex))
				{
					CharacterAudioComponent->SetSound(DeathSounds[RandomDeathSoundIndex]);
					CharacterAudioComponent->Play();
				}

			}
			SetLifeSpan(3.0f);
		}
	}

	return ActualDamage;
}

