// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "Public/Pickable/PickUp.h"
#include "Item.generated.h"

/**Item struct for storing items:
 * APickUp* + it's count.
 */
USTRUCT ()
struct TROUNOIR_API FItem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory/Item")
	APickUp* ItemRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory/Item")
	int ItemCount;

public: 
	FItem();

	FItem(APickUp* ItemRef, int ItemCount);

	void IncreaseCount(int count);

	bool operator==(FItem other);

	/*APickUp* Pull (int count = 1);*/
	//bool operator= (FItem& other);
};
