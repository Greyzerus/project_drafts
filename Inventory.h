// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Public/Pickable/PickUp.h"
#include "Public/Inventory/Item.h"
#include "Inventory.generated.h"

/**
 *	Base class for storing APickable as items
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TROUNOIR_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:

	UInventory();

protected:

	/*this is a core element set of */
	TArray <FItem> items;

	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float weight;

	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float max_weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	int max_volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	bool bStackable;

public:

	virtual void BeginPlay() override;

	/*virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;*/

public:

	/*Adds items according to their "item.stacable" field.
	Nonstackable ones added as separate items*/

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Add (APickUp* item, uint16 count = 1) virtual;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool IsContains(APickUp* const item) const;

	/* We don't need this due to "protected", do we?
	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	int Volume();
	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	float Weight();*/
	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	bool IsEmpty();
	//UFUNCTION(BlueprintCallable, Category = "Inventory")
	/*APickUp* Pull //How will we choose at which item would we call?*/

};



/*
"GREAT IDEAS"
	
  /!WE NEED TO DEFINE ALL SUBCLASSES METHODS IN APickUp 
	As deleted virtual functions if we wanna have no troubles with templates.

  /!Whats about items id?
*/