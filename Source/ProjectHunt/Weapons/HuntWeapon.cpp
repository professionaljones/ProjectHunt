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
	//Collision parameters
	FCollisionQueryParams CollisionParameters;

	//this->Execute_OnFire(this);

	if (WeaponOwner == UGameplayStatics::GetPlayerCharacter(GetWorld(),0))
	{
		
		StartLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0)->GetRootComponent()->GetComponentLocation();
		EndLocation = StartLocation + (UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetForwardVector() * WeaponStatsData.WeaponDistanceRange);
		UE_LOG(ProjectHunt, Log, TEXT("Player shooting"));
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

	

	//	AAsylumPlayerCharacter* PChar = Cast<AAsylumPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		//The StartLocation of the raycast
		//StartLocation = PChar->FollowCamera->GetComponentLocation();

		//The EndLocation of the raycast
		//EndLocation = StartLocation + (PChar->FollowCamera->GetForwardVector() * WeaponRange);
		//UE_LOG(LogTemp, Warning, TEXT("Using Third Person Camera"));

		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, 5.0f, 5, 5.0f);
	//Single line trace
		if (GetWorld()->LineTraceSingleByObjectType(SingleHit, StartLocation, EndLocation, ObjectsToTarget, CollisionParameters))
		{
		
			//If we hit something and said target is what we are looking for
			if (SingleHit.bBlockingHit && IsValid(HitActor))
			{
				UE_LOG(ProjectHunt, Log, TEXT("Player hit target"));
				//Apply damage
				UGameplayStatics::ApplyPointDamage(HitActor, WeaponStatsData.TotalDamage, SingleHit.ImpactPoint, SingleHit, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, nullptr);

				//this->Execute_OnHitTarget(this);
				//this->Execute_OnWeaponActivate(this, GetWeaponAmmoType());
			
			}
	
		}
	}

void AHuntWeapon::CalculateDamage()
{
	WeaponStatsData.TotalDamage = WeaponStatsData.BaseDamage * (WeaponStatsData.DamageMultiplierAmount + WeaponStatsData.DamageModifierAmount);
}

EAmmoType AHuntWeapon::GetWeaponAmmoType()
{
	return WeaponStatsData.WeaponAmmoType;
}

void AHuntWeapon::StartFire()
{
	if (bCanWeaponCharge)
	{
		StartCharge();
	}
	else
	{
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
	}
	if (GetWorldTimerManager().IsTimerActive(AutoFireTimer))
	{
		GetWorldTimerManager().ClearTimer(AutoFireTimer);
	}
}

void AHuntWeapon::StartCharge()
{
	GetWorldTimerManager().SetTimer(ChargeFireTimer, this, &AHuntWeapon::Charge, WeaponStatsData.ChargeRate, true);
}

void AHuntWeapon::Charge()
{
	CurrentWeaponCharge = CurrentWeaponCharge + AmountToCharge;
	WeaponStatsData.DamageModifierAmount = CurrentWeaponCharge;
	if (CurrentWeaponCharge >= WeaponStatsData.WeaponChargeLimit)
	{
		CurrentWeaponCharge = WeaponStatsData.WeaponChargeLimit;
	}
}

void AHuntWeapon::FinishCharge()
{
	GetWorldTimerManager().ClearTimer(ChargeFireTimer);
	//Reset Charge value
	CurrentWeaponCharge = 0.f;
	//Reset Damage modifier
	WeaponStatsData.DamageModifierAmount = 1.0f;
	//Attempt to apply damage
	FireWeapon();
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

