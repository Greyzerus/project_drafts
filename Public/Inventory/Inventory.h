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
	float volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float max_weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	float max_volume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	bool bStackable;

public:

	virtual void BeginPlay() override;

	/*virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;*/

public:

	UFUNCTION(BlueprintCallable, Category="Inventory")
	virtual void Add (APickUp* item, int count = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	APickUp* Take(FItem& item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<APickUp*> MultyTake(FItem& item, int count);

public:
	/*getters*/
	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	FORCEINLINE float GetVolume() { return volume; }

	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	FORCEINLINE float GetWeight() { return weight; }

	/*setters*/
	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	void SetMaxVolume(float NewVolume) { max_volume = NewVolume; }

	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	void SetMaxWeight(float NewWeight) { max_weight = NewWeight; }

	/*bool*/
	UFUNCTION(BlueprintCallable, Category = "Inventory.Inf")
	FORCEINLINE bool IsEmpty() { return !!items.Num(); };

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE bool IsContains(APickUp* const item);
};



/*
"GREAT IDEAS"
  /!Whats about items id?
*/