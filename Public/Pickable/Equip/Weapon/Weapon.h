// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickable/Equip/Equip.h"
#include "Components/ArrowComponent.h"
#include "Public/Pickable/Ammo/Ammo.h"
#include "Public/Condition/CoreConditions_common.h"

#include "Public/Inventory/Inventory.h"
#include "Weapon.generated.h"


UCLASS()
class TROUNOIR_API AWeapon : public AEquip
{
	GENERATED_BODY()
	
public:

	AWeapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
	UArrowComponent* ShootDirection;

public:

	virtual void Shoot();

	virtual void Activate();

	virtual void Deactivate();
};
