// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectHuntCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ProjectHunt/Weapons/HuntWeapon.h"
#include "ProjectHunt/Character/HuntStatsComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AProjectHuntCharacter

AProjectHuntCharacter::AProjectHuntCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	//Create a StatsComponent
	StatsComponent = CreateDefaultSubobject<UHuntStatsComponent>("StatsComponent");

	//Create a AudioComponent
	CharacterAudioComponent = CreateDefaultSubobject<UAudioComponent>("CharacterAudioComponent");

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));



}

void AProjectHuntCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	StartStyleModTimer();
	MaxStyleAmount = SSS_StyleLimit;
	

}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectHuntCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AProjectHuntCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AProjectHuntCharacter::OnFireEnd);
	


	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AProjectHuntCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjectHuntCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AProjectHuntCharacter::TurnCharacter);
	PlayerInputComponent->BindAxis("TurnRate", this, &AProjectHuntCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AProjectHuntCharacter::LookUpAtCamera);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AProjectHuntCharacter::LookUpAtRate);
}

void AProjectHuntCharacter::ModifyStyle(float StyleModAmount)
{
	float Mod = 1.0f * StyleAmountMultiplier;
	CurrentStyleAmount += Mod;
	if (CurrentStyleAmount > 0.0f)
	{
		StartStyleModTimer();
		//CurrentStyleAmount -= 1.0f;
	}

	UpdateStylePercentage();

}

void AProjectHuntCharacter::DecreaseStyle()
{
	CurrentStyleAmount -= DamageStyleAmount * StyleAmountMultiplier;
	UpdateStylePercentage();
}

void AProjectHuntCharacter::UpdateStylePercentage()
{
	StylePercentage = CurrentStyleAmount / MaxStyleAmount;
	if (CurrentStyleAmount)
	{
		if (StylePercentage <= D_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_Dull;
		
		}
		if (StylePercentage > C_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_Crazy;
			
		}
		if (StylePercentage > B_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_Blast;
			
		}

		if (StylePercentage > A_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_Alright;
			
		}
		if (StylePercentage > S_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_Showtime;
		}
		if (StylePercentage > SS_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_Stylish;
		}
		if (StylePercentage > SSS_StyleLimit)
		{
			PlayerStyle = ECharacterStyleRank::SR_SuperStylish;
		}
	}
	
}

void AProjectHuntCharacter::StartStyleModTimer()
{
	if (CurrentStyleAmount >= 0.0f)
	{
		if (!GetWorldTimerManager().IsTimerActive(StyleDecreaseTimer))
		{
			GetWorldTimerManager().SetTimer(StyleDecreaseTimer, this, &AProjectHuntCharacter::DecreaseStyle, 1.0f, true);
		}
		
	}
	if (CurrentStyleAmount <= 0.0f)
	{
		GetWorldTimerManager().PauseTimer(StyleDecreaseTimer);
	}
	
}

float AProjectHuntCharacter::GetStylePercentage()
{
	return StylePercentage;
}

float AProjectHuntCharacter::GetCurrentStyleAmount()
{
	return CurrentStyleAmount;
}

void AProjectHuntCharacter::OnFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}



void AProjectHuntCharacter::OnFireEnd()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->EndFire();
		
		//CurrentWeaponCharge = 0.f;
	}
}

void AProjectHuntCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AProjectHuntCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AProjectHuntCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void AProjectHuntCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AProjectHuntCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AProjectHuntCharacter::TurnCharacter(float Rate)
{
	float NewTurn = Rate * MyPlayerController->GetLookXSensitivity_PC();
	AddControllerYawInput(NewTurn * GetWorld()->GetDeltaSeconds());
}

void AProjectHuntCharacter::LookUpAtCamera(float Rate)
{
	float NewLookUp = Rate * MyPlayerController->GetLookYSensitivity_PC();
	AddControllerYawInput(NewLookUp * GetWorld()->GetDeltaSeconds());
}

void AProjectHuntCharacter::TurnAtRate(float Rate)
{
	BaseTurnRate =  MyPlayerController->GetLookXSensitivity_Gamepad();
	
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AProjectHuntCharacter::LookUpAtRate(float Rate)
{
	BaseLookUpRate = MyPlayerController->GetLookYSensitivity_Gamepad();
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AProjectHuntCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProjectHuntCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AProjectHuntCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AProjectHuntCharacter::TouchUpdate);
		return true;
	}

	return false;
}

float AProjectHuntCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (DamageAmount > 0.0f)
	{
		if (this->CanBeDamaged())
		{
			//StatsComponent->CurrentHealth -= (DamageAmount * DamageTakenModifier);
			StatsComponent->DamageHealth(DamageAmount * DamageTakenModifier);
			DecreaseStyle();
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
