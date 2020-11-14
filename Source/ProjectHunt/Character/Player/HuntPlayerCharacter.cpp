// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#define SAVEDATAFILENAME "SampleSavedData"

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

	PlayerStatsComponent->MaxHealth = 200.0f;
	PlayerStatsComponent->MaxAragon = 200.0f;
	PlayerStatsComponent->CurrentHealth = PlayerStatsComponent->MaxHealth;
	PlayerStatsComponent->CurrentAragon = PlayerStatsComponent->MaxAragon;
	PlayerStatsComponent->AragonRechargeAmount = 15.0f;
	MaxStyleAmount = SSS_StyleLimit;

	//Create a secondary AudioComponent 
	SuitAudioComponent = CreateDefaultSubobject<UAudioComponent>("SuitAudioComponent");
	MovementSpeed = 1300.0f;
}

void AHuntPlayerCharacter::CharacterTakeDamage(float DamageAmount)
{
	PlayerStatsComponent->DamageHealth(DamageAmount * DamageTakenModifier);
	UpdatePlayerData();
}

bool AHuntPlayerCharacter::IsCharacterDead()
{
	return PlayerStatsComponent->bIsDead;
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
	return PlayerSavedStats.bHasMissileLauncher;
}

bool AHuntPlayerCharacter::CanPlayerUseAragon()
{
	return PlayerSavedStats.bUnlockedAragon;
}

bool AHuntPlayerCharacter::CanPlayerDash()
{
	return PlayerSavedStats.bUnlockedDash;
}

bool AHuntPlayerCharacter::CanPlayerWallrun()
{
	return PlayerSavedStats.bUnlockedWallrun;
}

void AHuntPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyPlayerController = Cast<AHuntPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UpdatePlayerData();

}

bool AHuntPlayerCharacter::SaveData()
{
	//Save the data to binary
	FBufferArchive ToBinary;
	SaveLoadData(ToBinary, PlayerStatsComponent->CurrentHealth, PlayerStatsComponent->MaxHealth, PlayerStatsComponent->CurrentAragon, PlayerStatsComponent->MaxAragon);

	//No data were saved
	if (ToBinary.Num() <= 0) return false;

	//Save binaries to disk
	bool result = FFileHelper::SaveArrayToFile(ToBinary, TEXT(SAVEDATAFILENAME));

	//Empty the buffer's contents
	ToBinary.FlushCache();
	ToBinary.Empty();

	return result;
}

bool AHuntPlayerCharacter::LoadData()
{
	TArray<uint8> BinaryArray;

	//load disk data to binary array
	if (!FFileHelper::LoadFileToArray(BinaryArray, TEXT(SAVEDATAFILENAME))) return false;

	if (BinaryArray.Num() <= 0) return false;

	//Memory reader is the archive that we're going to use in order to read the loaded data
	FMemoryReader FromBinary = FMemoryReader(BinaryArray, true);
	FromBinary.Seek(0);

	SaveLoadData(FromBinary, PlayerStatsComponent->CurrentHealth, PlayerStatsComponent->MaxHealth, PlayerStatsComponent->CurrentAragon, PlayerStatsComponent->MaxAragon);

	//Empty the buffer's contents
	FromBinary.FlushCache();
	BinaryArray.Empty();
	//Close the stream
	FromBinary.Close();

	return true;
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
	switch (CurrentPlayerSuit)
	{
	case EPlayerSuit::Suit_Standard:

		DamageDefenseModifer = 0.0f;

	case EPlayerSuit::Suit_Version2:

		DamageDefenseModifer = 0.15f;

	case EPlayerSuit::Suit_Version3:

		DamageDefenseModifer = 0.30f;

	case EPlayerSuit::Suit_Version4:

		DamageDefenseModifer = 0.50f;

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

void AHuntPlayerCharacter::SetPlayerStats(float NewMaxHealth, float NewMaxAragon, EPlayerSuit NewPlayerSuit, ESuitMainAbilities NewSuitPower, ESuitPowerModifiers NewPowerModifierOne, ESuitPowerModifiers NewPowerModifierTwo, int32 NewMaxMissileCount, FPlayerSaveableStats NewPlayerSaveableStats, TMap<int32, AHuntWeapon*> NewWeaponInventory, int32 NewCurrentDataPoints)
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
	PlayerSavedStats = NewPlayerSaveableStats;
	UpdatePlayerData();
	IHuntCharacterInterface::Execute_UpdateStatsUI(this);


}

void AHuntPlayerCharacter::SaveLoadData(FArchive& Ar, float& CurrentHealth, float& MaxHealth, float& CurrentAragon, float& MaxAragon)
{
	Ar << PlayerStatsComponent->CurrentHealth;
	Ar << PlayerStatsComponent->MaxHealth;
	Ar << PlayerStatsComponent->CurrentAragon;
	Ar << PlayerStatsComponent->MaxAragon;
	//Ar << PlayerLocationToSaveOrLoad = new FTransform(new Vector3(0), new Vector3(0), new Vector3(0));
	//Ar << UGameplayStatics::GetPlayerCharacter(GetWorld(),0)->GetActorTransform();
}

