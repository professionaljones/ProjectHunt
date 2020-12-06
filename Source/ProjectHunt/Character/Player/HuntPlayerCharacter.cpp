// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"
#include "Camera/CameraComponent.h"

AHuntPlayerCharacter::AHuntPlayerCharacter()
{

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	PlayerStatsComponent = CreateDefaultSubobject<UPlayerStatsComponent>("PlayerStatsComponent");
	//PlayerStatsComponent->RegisterComponent();
	////this->AddInstanceComponent(PlayerStatsComponent);

	PlayerStatsComponent->MaxHealth = 200.0f;
	PlayerStatsComponent->MaxAragon = 200.0f;
	PlayerStatsComponent->CurrentHealth = PlayerStatsComponent->MaxHealth;
	PlayerStatsComponent->CurrentAragon = PlayerStatsComponent->MaxAragon;
	PlayerStatsComponent->AragonRechargeAmount = 15.0f;
	MaxStyleAmount = SSS_StyleLimit;

	//Create a secondary AudioComponent 
	SuitAudioComponent = CreateDefaultSubobject<UAudioComponent>("SuitAudioComponent");
	//SuitAudioComponent = 
	MovementSpeed = 900.0f;

	GetCharacterMovement()->MaxAcceleration = 4096.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1024.0f;
	GetCharacterMovement()->AirControl = PlayerAirControl;
}

void AHuntPlayerCharacter::CharacterTakeDamage(float DamageAmount)
{
	PlayerStatsComponent->DamageHealth(DamageAmount * DamageTakenModifier);
	if (PlayerStatsComponent->bIsDead)
	{
		PlayerStatsComponent->OnDeathDelegate.Broadcast();
	}
	
}

bool AHuntPlayerCharacter::IsCharacterDead()
{
	return PlayerStatsComponent->bIsDead;
}

void AHuntPlayerCharacter::OnActivatePower()
{
	PlayerStatsComponent->ActivatePower();

}

void AHuntPlayerCharacter::OnRechargePower()
{
	PlayerStatsComponent->RechargeAragon();

}

void AHuntPlayerCharacter::CharacterActivatePower()
{
	PlayerActivatePower();
	IHuntCharacterInterface::Execute_OnActivateAragonPower(this, PlayerStatsComponent->CurrentSuitPower);
}

void AHuntPlayerCharacter::CharacterDeactivatePower()
{
	PlayerStatsComponent->DeactivatePower();
	//PlayerStatsComponent->bIsPowerActive = false;
	GetWorldTimerManager().ClearTimer(PlayerActivePowerHandle);
	PlayerRechargeAragon();
	IHuntCharacterInterface::Execute_UpdateStatsUI(this);
	//IHuntCharacterInterface::Execute_OnDeactivateAragonPower(this, PlayerStatsComponent->CurrentSuitPower);
}

void AHuntPlayerCharacter::CharacterRechargeAragon()
{
	if (PlayerStatsComponent->CurrentAragon >= PlayerStatsComponent->MaxAragon)
	{
		GetWorldTimerManager().ClearTimer(PlayerRechargeAragonHandle);
	}
	PlayerStatsComponent->RechargeAragon();
	IHuntCharacterInterface::Execute_UpdateStatsUI(this);
}

void AHuntPlayerCharacter::CharacterUseAragon()
{
	PlayerStatsComponent->ConsumeAragon_Power();

	IHuntCharacterInterface::Execute_UpdateStatsUI(this);
}

void AHuntPlayerCharacter::PlayerActivatePower()
{
	if (PlayerRechargeAragonHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(PlayerRechargeAragonHandle);
	}
	if (bUnlockedAragon)
	{
		PlayerStatsComponent->bIsPowerActive = true;
		OnActivatePower();
		GetWorldTimerManager().SetTimer(PlayerActivePowerHandle, this, &AHuntPlayerCharacter::CharacterUseAragon, 1.0f, true);
		/*if (GetWorldTimerManager().IsTimerActive(PlayerRechargeAragonHandle) || PlayerStatsComponent->bIsRecharging)
		{
			GetWorldTimerManager().ClearTimer(PlayerRechargeAragonHandle);
			PlayerStatsComponent->bIsRecharging = false;
		}*/
		//GetWorldTimerManager().SetTimer(PlayerActivePowerHandle, this, &AHuntPlayerCharacter::CharacterActivatePower, 1.0f, true);
	}

}

void AHuntPlayerCharacter::PlayerRechargeAragon()
{
	if (!PlayerStatsComponent->bIsPowerActive)
	{
		if (PlayerStatsComponent->bIsAragonEmpty || PlayerStatsComponent->bIsRecharging)
		{
			GetWorldTimerManager().SetTimer(PlayerRechargeAragonHandle, this, &AHuntPlayerCharacter::CharacterRechargeAragon, 1.0f, true);
		}
		if (PlayerActivePowerHandle.IsValid())
		{
			GetWorldTimerManager().ClearTimer(PlayerActivePowerHandle);
		}
	}
	
	
}

void AHuntPlayerCharacter::UpdatePlayerData()
{
	PlayerSavedData.SaveCurrentHealth = PlayerStatsComponent->CurrentHealth;
	PlayerSavedData.SaveMaxHealth = PlayerStatsComponent->MaxHealth;
	PlayerSavedData.SaveCurrentAragon = PlayerStatsComponent->CurrentAragon;
	PlayerSavedData.SaveMaxAragon = PlayerStatsComponent->MaxAragon;
	PlayerSavedData.SaveCurrentMissileCount = CurrentMissileCount;
	PlayerSavedData.SaveMaxMissileCount = MaxMissileCount;
	PlayerSavedData.SaveCurrentPlayerSuit = CurrentPlayerSuit;
	PlayerSavedData.SaveCurrentDashCount = CurrentDashCount;
	PlayerSavedData.SaveMaxDashCount = MaxDashCount;
	PlayerSavedData.SaveMaxJumpCount = MaxJumpCount;
	PlayerSavedData.SaveCurrentJumpCount = CurrentJumpCount;
}

int32 AHuntPlayerCharacter::GetJumpCount()
{
	return CurrentJumpCount;
}

int32 AHuntPlayerCharacter::GetDashCount()
{
	return CurrentDashCount;
}

bool AHuntPlayerCharacter::CanPlayerUseMissiles()
{
	return bHasMissileLauncher;
}

bool AHuntPlayerCharacter::CanPlayerUseAragon()
{
	return bUnlockedAragon;
}

bool AHuntPlayerCharacter::CanPlayerDash()
{
	return bUnlockedDash;
}

bool AHuntPlayerCharacter::CanPlayerWallrun()
{
	return bUnlockedWallrun;
}

void AHuntPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//MyPlayerController = Cast<AHuntPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//UpdatePlayerData();

}



void AHuntPlayerCharacter::UnlockAbility(bool AbilityToToggle, bool bUnlockAbility)
{
	AbilityToToggle = bUnlockAbility;
	UpdatePlayerData();
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
	if (CanPlayerUseMissiles())
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
	if (bAreMissilesEmpty == true)
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
	UpdatePlayerData();
}

void AHuntPlayerCharacter::UpdateMissileCapacity(int32 NewMissileAmount)
{
	MaxMissileCount = NewMissileAmount;
	CurrentMissileCount = MaxMissileCount;
	UpdatePlayerData();
}

void AHuntPlayerCharacter::SetPlayerSuit(EPlayerSuit NewPlayerSuit)
{
	CurrentPlayerSuit = NewPlayerSuit;
	switch (CurrentPlayerSuit)
	{
	case EPlayerSuit::Suit_Standard:
	{
		PlayerStatsComponent->ModifyStandardResistance(-1.0f);
		PlayerStatsComponent->ModifyFireResistance(-2.0f);
		PlayerStatsComponent->ModifyIceResistance(-1.50f);
		PlayerStatsComponent->ModifyShockResistance(-2.25f);
		PlayerStatsComponent->ModifyAragonResistance(-3.0f);
		break;
	}


	case EPlayerSuit::Suit_Version2:
	{
		PlayerStatsComponent->ModifyStandardResistance(-0.75f);
		PlayerStatsComponent->ModifyFireResistance(-1.75f);
		PlayerStatsComponent->ModifyIceResistance(-1.25f);
		PlayerStatsComponent->ModifyShockResistance(-2.0f);
		PlayerStatsComponent->ModifyAragonResistance(-3.0f);
		break;
	}
	case EPlayerSuit::Suit_Version3:

	{
		PlayerStatsComponent->ModifyStandardResistance(-0.65f);
		PlayerStatsComponent->ModifyFireResistance(-1.0f);
		PlayerStatsComponent->ModifyIceResistance(-0.75f);
		PlayerStatsComponent->ModifyShockResistance(-1.50f);
		PlayerStatsComponent->ModifyAragonResistance(-2.50f);
	}

	case EPlayerSuit::Suit_Version4:
	{
		PlayerStatsComponent->ModifyStandardResistance(-0.50f);
		PlayerStatsComponent->ModifyFireResistance(-1.25f);
		PlayerStatsComponent->ModifyIceResistance(-1.0f);
		PlayerStatsComponent->ModifyShockResistance(-1.50f);
		PlayerStatsComponent->ModifyAragonResistance(-2.0f);
	}
	default:
		break;

	}
	UpdatePlayerData();
}

void AHuntPlayerCharacter::SetCurrentSuitPower(ESuitMainAbilities NewSuitPower)
{
	PlayerStatsComponent->CurrentSuitPower = NewSuitPower;
	UpdatePlayerData();
}

void AHuntPlayerCharacter::SetPowerModifierOne(ESuitPowerModifiers NewPowerModifier)
{
	PlayerStatsComponent->PowerModifierSlotOne = NewPowerModifier;
	UpdatePlayerData();
}

void AHuntPlayerCharacter::SetPowerModifierTwo(ESuitPowerModifiers NewPowerModifier)
{
	PlayerStatsComponent->PowerModifierSlotTwo = NewPowerModifier;
	UpdatePlayerData();
}

void AHuntPlayerCharacter::UpdateDashCount(int32 IncreaseAmount)
{
	MaxDashCount += IncreaseAmount;
	CurrentDashCount = MaxDashCount;
	UpdatePlayerData();

}

void AHuntPlayerCharacter::UpdateJumpCount(int32 IncreaseAmount)
{
	MaxJumpCount += IncreaseAmount;
	CurrentJumpCount = MaxDashCount;
	UpdatePlayerData();
}

void AHuntPlayerCharacter::SetPlayerStats(float NewMaxHealth, float NewMaxAragon, EPlayerSuit NewPlayerSuit, ESuitMainAbilities NewSuitPower, ESuitPowerModifiers NewPowerModifierOne, ESuitPowerModifiers NewPowerModifierTwo, int32 NewMaxMissileCount, TMap<int32, AHuntWeapon*> NewWeaponInventory, int32 NewCurrentDataPoints)
{
	PlayerStatsComponent->UpdateMaxHealth(NewMaxHealth);
	PlayerStatsComponent->UpdateMaxAragon(NewMaxAragon);
	SetPlayerSuit(NewPlayerSuit);
	SetCurrentSuitPower(NewSuitPower);
	SetPowerModifierOne(NewPowerModifierOne);
	SetPowerModifierTwo(NewPowerModifierTwo);
	UpdateMissileCapacity(NewMaxMissileCount);
	WeaponInventory = NewWeaponInventory;
	CurrentDataPoints = NewCurrentDataPoints;

	UpdatePlayerData();
	IHuntCharacterInterface::Execute_UpdateStatsUI(this);


}

void AHuntPlayerCharacter::SetPlayerAbilities(bool bEnableDash, bool bEnableWallrun, bool bEnableAragon, bool bEnableMissiles)
{
	IHuntPlayerInterface::Execute_OnPlayerUnlockDash(this, bEnableDash);
	IHuntPlayerInterface::Execute_OnPlayerUnlockWallrun(this, bEnableWallrun);
	IHuntPlayerInterface::Execute_OnPlayerUnlockAragon(this, bEnableMissiles);
	IHuntPlayerInterface::Execute_OnPlayerUnlockMissiles(this, bEnableMissiles);

}

