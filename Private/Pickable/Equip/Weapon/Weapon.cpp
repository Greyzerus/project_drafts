// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Pickable/Equip/Weapon/Weapon.h"


AWeapon::AWeapon()
{
	ShootDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Shoot Direction"));
	ShootDirection->AttachTo(Mesh, "Muzzle");
}

void AWeapon::Shoot()
{
	FRotator Direction = ShootDirection->GetComponentRotation();
	FVector Location = ShootDirection->GetComponentLocation();

	DrawDebugLine(
		GetWorld(),
		Location,
		Location + Direction.Vector() * 30,
		FColor(0, 255, 0), false, 5, 0, 1);

	AAmmo* ammo = GetWorld()->SpawnActor<AAmmo>(Location, Direction);
	//CapsuleComponent->AddImpulseAtLocation(ammo->GetShootImpulse(), Location);
}

void AWeapon::Activate()
{

}

void AWeapon::Deactivate()
{

}