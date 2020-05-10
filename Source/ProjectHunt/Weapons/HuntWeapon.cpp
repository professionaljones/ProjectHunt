// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntWeapon.h"
#include "ProjectHunt/ProjectHuntCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHuntWeapon::AHuntWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a skeletal mesh component that will be used
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	//Set mesh as root component
	RootComponent = WeaponMesh;
	//Create audio component that handles weapon SFX
	WeaponAudioComponent = CreateDefaultSubobject<UAudioComponent>("WeaponAudioComponent");

}

// Called when the game starts or when spawned
void AHuntWeapon::BeginPlay()
{
	Super::BeginPlay();

	CalculateDamage();
	ActorsToIgnore.Add(WeaponOwner);

}

// Called every frame
void AHuntWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHuntWeapon::FireWeapon()
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

	if (WeaponOwner == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{

		StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetComponentLocation();
		EndLocation = StartLocation + (UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetForwardVector() * WeaponStatsData.WeaponDistanceRange);

	}

	
	

	//Create temp variable for Actor we hit
	AActor* HitActor = SingleHit.GetActor();

	//Length of the ray in Unreal units
	float WeaponRange = WeaponStatsData.WeaponDistanceRange;

	//Play Fire SFX
	if (WeaponFireSound != NULL)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, WeaponFireSound, GetActorLocation());
		WeaponAudioComponent->SetSound(WeaponFireSound);
		WeaponAudioComponent->Play();
	}
	if (WeaponFireVFX != NULL)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponFireVFX, WeaponMesh->GetSocketTransform(WeaponMuzzlePoint), true, EPSCPoolMethod::AutoRelease, true);
	}

	if (bEnableDebugMode)
	{
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 5.0f, 5, 5.0f);
	}

	SpawnWeaponProjectile();
	IHuntWeaponInterface::Execute_OnWeaponFire(this);
	
}

void AHuntWeapon::FireCharge()
{
	if (bIsCharging)
	{
		if (WeaponProjectileState != EProjectileState::Projectile_Charge)
		{
			WeaponProjectileState = EProjectileState::Projectile_Charge;
		}
	}

	//Play Fire SFX
	if (WeaponFireSound != NULL)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, WeaponFireSound, GetActorLocation());
		WeaponAudioComponent->SetSound(WeaponChargeFireSound);
		WeaponAudioComponent->Play();
	}
	if (WeaponFireVFX != NULL)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponFireVFX, WeaponMesh->GetSocketTransform(WeaponMuzzlePoint), true, EPSCPoolMethod::AutoRelease, true);
	}
	IHuntWeaponInterface::Execute_OnWeaponFire(this);
}

void AHuntWeapon::CalculateDamage()
{
	WeaponStatsData.TotalDamage = WeaponStatsData.BaseDamage * (WeaponStatsData.DamageMultiplierAmount + WeaponStatsData.DamageModifierAmount);
}

EAmmoType AHuntWeapon::GetWeaponAmmoType()
{
	return WeaponStatsData.WeaponAmmoType;
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
			testDO = GetWorld()->SpawnActor<AHuntWeaponProjectile>(testDO::StaticClass(), WeaponMesh->GetSocketTransform(WeaponMuzzlePoint), SpawnParameters);
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
	if (bCanWeaponCharge)
	{
		FireWeapon();
		StartCharge();
	}
	else
	{
		if (WeaponProjectileState != EProjectileState::Projectile_Normal)
		{
			WeaponProjectileState = EProjectileState::Projectile_Normal;
		}
		if (WeaponStatsData.FireRate > 0.0f)
		{
			GetWorldTimerManager().SetTimer(AutoFireTimer, this, &AHuntWeapon::FireWeapon, WeaponStatsData.FireRate, true);
		}
		FireWeapon();
	}
}

void AHuntWeapon::EndFire()
{
	if (bCanWeaponCharge)
	{
		FinishCharge();
		GetWorldTimerManager().ClearTimer(ChargeFireTimer);
	}
	if (GetWorldTimerManager().IsTimerActive(AutoFireTimer))
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimer);
	}
}

void AHuntWeapon::StartCharge()
{
	
	GetWorldTimerManager().SetTimer(ChargeFireTimer, this, &AHuntWeapon::Charge, WeaponStatsData.ChargeRate, true,1.0f);
}

void AHuntWeapon::Charge()
{
	bIsCharging = true;
	CurrentWeaponCharge = CurrentWeaponCharge + AmountToCharge;
	WeaponStatsData.DamageModifierAmount = CurrentWeaponCharge;
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
	bIsCharging = false;
	//Attempt to apply damage
	if (CurrentWeaponCharge > 0.0f)
	{
		FireCharge();
		//Reset Charge value
		CurrentWeaponCharge = 0.f;
		//Reset Damage modifier
		WeaponStatsData.DamageModifierAmount = 1.0f;
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

