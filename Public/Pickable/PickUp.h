// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UCLASS()
class TROUNOIR_API APickUp : public AActor
{
	GENERATED_BODY()

public:
	APickUp();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	bool isPicked;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	float weight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
	float volume;
	
public:

	virtual bool operator==(APickUp& rs);

public: // the interface don't change world position of the object
	void PickUp(class UInventary* PickUpper);

	void UnPickUp();

public:
	bool IsPicked() { return isPicked; }

	float Weight() { return weight; }

	float Volume() { return volume; }
};
