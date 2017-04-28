// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Inventory/Inventory.h"


UInventory::UInventory():
		weight(0),
		volume(0),
		max_weight (0),
		max_volume (0),
		bStackable (true) 
{}


void UInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInventory::Add(APickUp* item, int count)
{
	//TODO reimplement
	float bufVolume = item->Volume() * count;
	float bufWeight = item->Weight() * count;
	while (count && (weight + bufWeight > max_weight || volume + bufVolume > max_volume)) {
		count--;
		bufVolume -= item->Volume();
		bufWeight -= item->Weight();
	}
	if (!count)
		return;
	//TODO down to there
	volume += bufVolume;
	weight += bufWeight;

	if (!bStackable) {
		for (int i = 0; i < count; i++)
			items.Emplace(item, 1);
		return;
	}
	for (auto & iter : items) 
		if (*iter.ItemRef == *item) {
			iter.ItemCount += count;
			return;
		}
	items.Emplace(item, count);
}

APickUp* UInventory::Take(FItem& item) {
	if (!IsContains(item.ItemRef))
		return nullptr;

	if (item.ItemCount == 1) {
		APickUp* ItemRef = item.ItemRef;
		items.Remove(item);
		return ItemRef;
	}
//ItemRef = item.ItemRef(item.ItemRef);
	APickUp* ItemRef = GetWorld()->SpawnActor<APickUp>(
		item.ItemRef->GetClass(), 
		item.ItemRef->GetActorTransform()
	);

	--item.ItemCount;
	volume -= item.ItemRef->Volume();
	weight -= item.ItemRef->Weight();
	return ItemRef;
}

TArray<APickUp*> UInventory::MultyTake(FItem& item, int count) {
	if (!IsContains(item.ItemRef))
		return  TArray<APickUp*>();

	int iters = FMath::Min(count, item.ItemCount);
	TArray<APickUp*> ItemsArray;
	for (int iter = 0; iter < iters; ++iter) {
		ItemsArray.Add(Take(item));
	}
	return ItemsArray;
}

bool UInventory::IsContains(APickUp* const item)
{
	if (item == nullptr)
		return false;
	for (auto & iter : items) {
		if (*iter.ItemRef == *item)
			return true;
	}
	return false;
}