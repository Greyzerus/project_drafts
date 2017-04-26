// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "Public/Pickable/PickUp.h"
#include "Item.generated.h"

/**Item struct for storing items:
 * APickUp* + it's count.
 */
USTRUCT (BlueprintReadOnly)
struct TROUNOIR_API FItem
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory/Item")
	APickUp* ItemRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory/Item")
	uint16 ItemCount;
public: 
	FItem();
	FItem(APickUp* ItemRef, uint16 ItemCount);
	~FItem();

	UFUNCTION(Category = "Inventory/Item")
	void IncreaseCount(uint16 count);

	bool operator== (FItem& other);

	/*APickUp* Pull (uint16 count = 1);*/
	//bool operator= (FItem& other);
};
