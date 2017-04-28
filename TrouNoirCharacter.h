// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"

#include "Public/Condition/Conditions.h"
#include "Public/Condition/ConditionTypes.h"
#include "Public/Damage/DamageTypes.h"

#include "Public/Pickable/Equip/Weapon/Weapon.h"

#include "TrouNoirCharacter.generated.h"

UCLASS(config=Game)
class ATrouNoirCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ATrouNoirCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AWeapon* Gun;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "1", meta = (AllowPrivateAccess = "true"))
	UConditions <
		ConditionsTypes::CoreConditions,
		ConditionsTypes::BaseConditions,
		DamageTypes::DamageType,
		ConditionsTypes::CoreConditions::CCS_COUNT,
		ConditionsTypes::BaseConditions::BCS_COUNT,
		DamageTypes::DamageType::DT_COUNT
	> states;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "1", meta = (AllowPrivateAccess = "true"))

protected:

	void OnResetVR();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Shoot();

	void Interact();

protected:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

