// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntWeapon.h"
#include "ProjectHunt/ProjectHuntCharacter.h"

// Sets default values
AHuntWeapon::AHuntWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a skeletal mesh component that will be used for First Person
	WeaponMeshFP = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshFP");
	//Create a skeletal mesh component that will be used for Third Person
	WeaponMeshTP = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshTP");
	//Set mesh as root component
	RootComponent = WeaponMeshFP;
	//Create audio component that handles weapon SFX
	WeaponAudioComponent = CreateDefaultSubobject<UAudioComponent>("WeaponAudioComponent");

	//Create secondary audio component that handles aux weapon SFX
	WeaponAltAudioComponent = CreateDefaultSubobject<UAudioComponent>("WeaponAltAudioComponent");

	//Create stimuli source component that registers for Hearing perception
	MyStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSourceComponent");

}

void AHuntWeapon::DelayWeaponFire()
{
	/*if (DelayFireHandle.IsValid())
	{
		if (GetWorldTimerManager().GetTimerRemaining(DelayFireHandle) != 0)
		{
			bCanFire = false;
		}
		else
		{
			bCanFire = true;
			GetWorldTimerManager().ClearTimer(DelayFireHandle);
		}
	}*/
	bCanFire = false;
	if (GetWorldTimerManager().GetTimerRemaining(DelayFireHandle) <= 0)
	{
		bCanFire = true;
		GetWorldTimerManager().ClearTimer(DelayFireHandle);
	}
}

EAmmoType AHuntWeapon::GetAmmoType()
{
	return WeaponStatsData.WeaponAmmoType;
}

bool AHuntWeapon::GetWeaponAmmoType(const TEnumAsByte<EWeaponAmmoType::Type> InFlag) const
{
	if (WeaponAmmoFlags != 0)
	{
		return true;
	}
	return false;
}

void AHuntWeapon::SetWeaponAmmoType(const TEnumAsByte<EWeaponAmmoType::Type> InFlag, const bool bSet)
{
	if (WeaponAmmoFlags <= 0)
	{
		WeaponAmmoFlags = InFlag;
		
	}
	
	
}

bool AHuntWeapon::GetIsFiring()
{
	return bIsFiring;
}

// Called when the game starts or when spawned
void AHuntWeapon::BeginPlay()
{
	Super::BeginPlay();

	CalculateDamage();
	ActorsToIgnore.Add(WeaponOwner);
	WeaponStatsData.OriginalDamageModifier = WeaponStatsData.DamageModifierAmount;
	WeaponStatsData.OriginalDamageMultiplier = WeaponStatsData.DamageMultiplierAmount;
	WeaponStatsData.OriginalChargeDamageModifier = WeaponStatsData.ChargeDamageModifierAmount;
	CalculateCritDamage();

}

// Called every frame
void AHuntWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHuntWeapon::FireWeapon()
{
	if (bCanFire)
	{
		if (!bIsCharging)
		{
			if (WeaponProjectileState != EProjectileState::Projectile_Normal)
			{
				WeaponProjectileState = EProjectileState::Projectile_Normal;
			}
		}

		//Collision parameters
		FCollisionQueryParams CollisionParameters;

		//this->Execute_OnFire(this);

		/*if (WeaponOwner == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{

			StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetComponentLocation();
			EndLocation = StartLocation + (UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetForwardVector() * WeaponStatsData.WeaponDistanceRange);

		}*/




		//Create temp variable for Actor we hit
		AActor* HitActor = SingleHit.GetActor();

		//Length of the ray in Unreal units
		//float WeaponRange = WeaponStatsData.WeaponDistanceRange;

		//Play Fire SFX
		if (WeaponFireSound != NULL)
		{
			WeaponAudioComponent->SetSound(WeaponFireSound);
			WeaponAudioComponent->Play();
		}
		if (WeaponFireVFX != NULL)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponFireVFX, WeaponMeshFP->GetSocketTransform(WeaponMuzzlePoint), true, EPSCPoolMethod::AutoRelease, true);
		}

		SpawnWeaponProjectile();
		CalculateDamage();
		bIsFiring = true;
		IHuntWeaponInterface::Execute_OnWeaponFire(this);
	}
	
	

}

void AHuntWeapon::FireCharge()
{
	if (bCanFire)
	{
		if (bIsCharging)
		{
			if (WeaponProjectileState != EProjectileState::Projectile_Charge)
			{
				WeaponProjectileState = EProjectileState::Projectile_Charge;
			}
		}

		//Play Fire SFX
		if (WeaponChargeFireSound != NULL)
		{
			WeaponAudioComponent->SetSound(WeaponChargeFireSound);
			WeaponAudioComponent->Play();
		}
		if (WeaponFireVFX != NULL)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponFireVFX, WeaponMeshFP->GetSocketTransform(WeaponMuzzlePoint), true, EPSCPoolMethod::AutoRelease, true);
		}
		CalculateDamage();
		bIsFiring = true;
		IHuntWeaponInterface::Execute_OnWeaponFire(this);
	}
	
}

void AHuntWeapon::FireUnique()
{
	if (bCanFire)
	{
		if (bCanWeaponFireUnique)
		{
			if (WeaponProjectileState != EProjectileState::Projectile_Charge)
			{
				WeaponProjectileState = EProjectileState::Projectile_Charge;
			}
		}
	}
	//Play Fire SFX
	if (WeaponChargeFireSound != NULL)
	{
		WeaponAudioComponent->SetSound(WeaponChargeFireSound);
		if (bCanFire)
		{
			WeaponAudioComponent->Play();
		}
		
	}
	if (WeaponFireVFX != NULL)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponFireVFX, WeaponMeshFP->GetSocketTransform(WeaponMuzzlePoint), true, EPSCPoolMethod::AutoRelease, true);
	}
	WeaponStatsData.DamageModifierAmount = WeaponStatsData.DamageMultiplierAmount * WeaponStatsData.ChargeDamageModifierAmount;
	CalculateDamage();
	bIsFiring = true;
	IHuntWeaponInterface::Execute_OnWeaponFireUnique(this);
}

void AHuntWeapon::ResetCharge()
{
	CurrentWeaponCharge = 0.0f;
	ResetDamage();
	bIsFiring = false;
}

void AHuntWeapon::CalculateDamage()
{
	WeaponStatsData.TotalDamage = WeaponStatsData.BaseDamage * (WeaponStatsData.DamageMultiplierAmount + WeaponStatsData.DamageModifierAmount);
}

void AHuntWeapon::CalculateCritDamage()
{
	WeaponStatsData.CriticalHitDamage = WeaponStatsData.BaseDamage * (WeaponStatsData.CriticalHitMultiplier + WeaponStatsData.DamageModifierAmount);
}

void AHuntWeapon::CalculateSpecialDamage()
{
	WeaponStatsData.TotalDamage = WeaponStatsData.BaseDamage * (WeaponStatsData.SpecialDamageMultiplier + WeaponStatsData.DamageModifierAmount);
}

void AHuntWeapon::ResetDamage()
{
	WeaponStatsData.DamageModifierAmount = WeaponStatsData.OriginalDamageModifier;
	WeaponStatsData.DamageMultiplierAmount = WeaponStatsData.OriginalDamageMultiplier;
	CalculateDamage();
}


void AHuntWeapon::SpawnWeaponProjectile()
{
	/*FActorSpawnParameters SpawnParameters;
	TSubclassOf<AHuntWeaponProjectile>* test = WeaponProjectiles.Find(WeaponProjectileState);
	class AHuntWeaponProjectile* testDO = test->GetDefaultObject();



	switch (WeaponProjectileState)
	{
	case EProjectileState::Projectile_Normal:
	{
		if (WeaponProjectiles.Find(Projectile_Normal))
		{
			testDO = GetWorld()->SpawnActor<AHuntWeaponProjectile>(testDO::StaticClass(), WeaponMeshFP->GetSocketTransform(WeaponMuzzlePoint), SpawnParameters);
		}

	}
	case EProjectileState::Projectile_Charge:
	{

	}
	case EProjectileState::Projectile_Alt:
	{

	}
	case EProjectileState::Projectile_ChargeAlt:
	{

	}
	}*/
}

void AHuntWeapon::StartFire()
{
	//ResetDamage();
	//CalculateDamage();
	if (bCanWeaponCharge)
	{
		FireWeapon();
		StartCharge();
	}
	else if (bCanWeaponFireUnique)
	{
		if (WeaponOwner->GetClass()->ImplementsInterface(UHuntPlayerInterface::StaticClass()))
		{
			if (IHuntPlayerInterface::Execute_GetPlayerAimStatus(WeaponOwner))
			{
				FireUnique();
			}
			else
			{
				FireWeapon();
			}
		}
		
		
	}
	else
	{
		if (WeaponProjectileState != EProjectileState::Projectile_Normal)
		{
			WeaponProjectileState = EProjectileState::Projectile_Normal;
		}
		if (WeaponStatsData.FireRate > 0.0f)
		{
			GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AHuntWeapon::DelayWeaponFire, WeaponStatsData.FireRate, false);
		}
		FireWeapon();
	}
}

void AHuntWeapon::EndFire()
{
	if (bIsFiring)
	{
		bIsFiring = false;
	}
	if (GetWorldTimerManager().IsTimerActive(ChargeFireTimer))
	{
		GetWorldTimerManager().ClearTimer(ChargeFireTimer);
	}
	if (bIsCharging)
	{
		FinishCharge();

		bIsCharging = false;
	}
	if (GetWorldTimerManager().IsTimerActive(AutoFireTimer))
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimer);
	}
	WeaponAltAudioComponent->Stop();
	GetWorldTimerManager().SetTimer(ResetDamageTimer, this, &AHuntWeapon::ResetCharge, 0.02f, false, 0.0f);
}

void AHuntWeapon::StartCharge()
{
	//Play Fire SFX
	if (WeaponChargingSound != NULL)
	{
		WeaponAltAudioComponent->SetSound(WeaponChargingSound);
		WeaponAltAudioComponent->Play();
	}
	GetWorldTimerManager().SetTimer(ChargeFireTimer, this, &AHuntWeapon::Charge, WeaponStatsData.ChargeRate, true, WeaponStatsData.WeaponChargeDelay);
}

void AHuntWeapon::Charge()
{
	bIsCharging = true;
	CurrentWeaponCharge = CurrentWeaponCharge + AmountToCharge;
	WeaponStatsData.DamageModifierAmount = CurrentWeaponCharge * WeaponStatsData.ChargeDamageModifierAmount;
	if (CurrentWeaponCharge > 0.0f)
	{
		if (WeaponProjectileState != EProjectileState::Projectile_Charge)
		{
			WeaponProjectileState = EProjectileState::Projectile_Charge;
		}
	}
	if (CurrentWeaponCharge >= WeaponStatsData.WeaponChargeLimit)
	{
		CurrentWeaponCharge = WeaponStatsData.WeaponChargeLimit;
	}
}

void AHuntWeapon::FinishCharge()
{

	//Attempt to apply damage
	if (CurrentWeaponCharge > 0.0f)
	{
		FireCharge();
		//Reset Charge value

		WeaponAltAudioComponent->Stop();
	}

	WeaponProjectileState = EProjectileState::Projectile_Normal;

}

void AHuntWeapon::AttachToOwner()
{

}

void AHuntWeapon::SetWeaponOwner(AProjectHuntCharacter* NewOwner)
{
	if (WeaponOwner == nullptr)
	{
		WeaponOwner = NewOwner;
	}
}

void AHuntWeapon::SetWeaponStats(FWeaponStatsData NewWeaponStats)
{
	//TODO: Find way to validate data

	WeaponStatsData.BaseDamage = NewWeaponStats.BaseDamage;
	WeaponStatsData.DamageMultiplierAmount = NewWeaponStats.DamageMultiplierAmount;
	WeaponStatsData.DamageModifierAmount = NewWeaponStats.DamageModifierAmount;
	WeaponStatsData.CriticalHitMultiplier = NewWeaponStats.CriticalHitMultiplier;
	WeaponStatsData.ChargeRate = NewWeaponStats.ChargeRate;
	WeaponStatsData.WeaponChargeDelay = NewWeaponStats.WeaponChargeDelay;
	WeaponStatsData.WeaponChargeLimit = NewWeaponStats.WeaponChargeLimit;
	WeaponStatsData.FireRate = NewWeaponStats.FireRate;
	WeaponStatsData.SpecialDamageMultiplier = NewWeaponStats.SpecialDamageMultiplier;
	WeaponStatsData.WeaponDamageLevel = NewWeaponStats.WeaponDamageLevel;
	WeaponStatsData.FireRateLevel = NewWeaponStats.FireRateLevel;
	WeaponStatsData.ChargeRateLevel = NewWeaponStats.ChargeRateLevel;
	WeaponStatsData.ChargeLimitLevel = NewWeaponStats.ChargeLimitLevel;
	WeaponStatsData.MaxWeaponLevel = NewWeaponStats.MaxWeaponLevel;
}

void AHuntWeapon::UpgradeDamage(float IncreaseAmount)
{
	WeaponStatsData.DamageModifierAmount = WeaponStatsData.DamageModifierAmount + IncreaseAmount;
	WeaponStatsData.WeaponDamageLevel++;
	if (WeaponStatsData.WeaponDamageLevel >= WeaponStatsData.MaxWeaponLevel)
	{
		WeaponStatsData.WeaponDamageLevel = WeaponStatsData.MaxWeaponLevel;
	}
	CalculateDamage();
}

void AHuntWeapon::UpgradeFireRate(float IncreaseAmount)
{
	WeaponStatsData.FireRate = WeaponStatsData.FireRate + IncreaseAmount;
	WeaponStatsData.FireRateLevel++;
	if (WeaponStatsData.FireRateLevel >= WeaponStatsData.MaxWeaponLevel)
	{
		WeaponStatsData.FireRateLevel = WeaponStatsData.MaxWeaponLevel;
	}
}

void AHuntWeapon::UpgradeChargeRate(float IncreaseAmount)
{
	WeaponStatsData.ChargeRate = WeaponStatsData.ChargeRate - IncreaseAmount;
	WeaponStatsData.ChargeRateLevel++;
	if (WeaponStatsData.ChargeRateLevel >= WeaponStatsData.MaxWeaponLevel)
	{
		WeaponStatsData.ChargeRateLevel = WeaponStatsData.MaxWeaponLevel;
	}
}

void AHuntWeapon::UpgradeChargeLimit(float IncreaseAmount)
{
	WeaponStatsData.WeaponChargeLimit = WeaponStatsData.WeaponChargeLimit + IncreaseAmount;
	WeaponStatsData.ChargeLimitLevel++;
	if (WeaponStatsData.ChargeLimitLevel >= WeaponStatsData.MaxWeaponLevel)
	{
		WeaponStatsData.ChargeLimitLevel = WeaponStatsData.MaxWeaponLevel;
	}
}

void AHuntWeapon::UpgradeDamageMultiplier(float IncreaseAmount)
{
	WeaponStatsData.DamageMultiplierAmount = WeaponStatsData.DamageMultiplierAmount + IncreaseAmount;
	WeaponStatsData.OriginalDamageMultiplier = WeaponStatsData.DamageMultiplierAmount;
	CalculateDamage();

}

void AHuntWeapon::UpgradeDamageModifier(float IncreaseAmount)
{
	WeaponStatsData.DamageModifierAmount = WeaponStatsData.DamageModifierAmount + IncreaseAmount;
	WeaponStatsData.OriginalDamageModifier = WeaponStatsData.DamageModifierAmount;
	CalculateDamage();
}

void AHuntWeapon::ResetDamageMultiplier()
{
	WeaponStatsData.DamageMultiplierAmount = 1.0f;
	CalculateDamage();
}

void AHuntWeapon::ResetDamageModifier()
{
	WeaponStatsData.DamageModifierAmount = 0.0f;
	CalculateDamage();
}

