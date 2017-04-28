// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "EmplyeeThruser.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TROUNOIR_API UEmplyeeThruser : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEmplyeeThruser();

	virtual void BeginPlay() override;
		
	/*Attaches thruster to the components*/
	void Inicialisate(UPrimitiveComponent* NewRotationTarget, UPrimitiveComponent* NewLocationTarget);

	void AddLinearForce(FVector new_Force);

	void AddRotationForce(FRotator &new_Force);

protected:

	bool IsInitialisated;

	/**
	* NOTE: positive rotations: (direction exaple for standart state)
	*					. Pitch	- z'-->x
	*					. Yaw	- y'-->x
	*					. Roll	- z'-->y
	*/

	// main Direction
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Thrust", meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* MainThrust;

	// Pitch Controll
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* TopThrust_P;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* BottomThrust_P;

	// Yaw controll
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* LeftThrust_Y;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* RightThrust_Y;

	// Roll controll
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* TopThrust_R;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UPhysicsThrusterComponent* BottomThrust_R;
};
