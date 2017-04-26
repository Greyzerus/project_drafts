// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Inventory/Inventory.h"


UInventory::UInventory():
		weight(0),
		volume(0),
		max_weight (0),
		max_volume (0),
		bStackable (true),
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

/*void UInventory::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}*/

void UInventory::Add(APickUp* item, uint16 count = 1)
{
	/*Without volume and weight processing.
	We not defined what will we do if we can add some of all elements or just can't*/
	volume += item->Volume() * count;
	weight += item->Weight() * count;
	if (!bStackable)
	{
		for (uint16 i = 0; i < count; i++)
		{
			items.emplace(item, 1);
		}
		return;
	}
	for (auto & iter : items)
	{
		if (*(iter.ItemRef) == *item)
		{
			iter.ItemCount += count;
			return;
		}
	}
	items.emplace(item, count);
	}
}


bool UInventory::IsContains(APickUp* const item) const
{
	for (auto & iter : items)
	{
		if (*(iter.ItemRef) == *element)
			return true;
	}
	return false;
}

bool UInventory::IsEmpty()
{
	return static_cast<bool> (items.num());
}
