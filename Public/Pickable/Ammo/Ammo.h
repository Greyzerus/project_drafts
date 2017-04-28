// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickable/PickUp.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ammo.generated.h"

/**
 * 
 */
UCLASS()
class TROUNOIR_API AAmmo : public APickUp
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AAmmo();

protected: /*********| members |*********/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InitialEnergy;

	FVector LastLocation;
	float Speed;

public: /*********| functions |*********/
	FVector GetShootImpulse();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const 
	{ return ProjectileMovement; }

protected:

	void PostInitProperties();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	void CalculateValues();

	void PrintTrace();
};
