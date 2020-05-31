// Copyright 2020 Brandon Jones. All Rights Reserved.


#include "HuntWeaponProjectile.h"

// Sets default values
AHuntWeaponProjectile::AHuntWeaponProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RootComponent = SphereCollision;

}

// Called when the game starts or when spawned
void AHuntWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHuntWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

