// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
* custom player controller
*/

#include "Components/ActorComponent.h"
#include "Public/Employee/EmployeeState.h"
#include "Public/Employee/EmplyeeThruser.h"
#include "EmployeeController.generated.h"


USTRUCT()
struct Flags_t {

	GENERATED_BODY()
	
	bool bLI_ignore = false;
	bool bRI_ignore = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TROUNOIR_API UEmployeeController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEmployeeController();

protected:	/**********************|    targets    |**********************/

	UPrimitiveComponent* RotationTarget;
	UPrimitiveComponent* LocationTarget;

	bool IsInitializated;

public:

	void Initialisate(UPrimitiveComponent* new_LocationTarget, UPrimitiveComponent* new_RotationTarget);
	void SetLocationTarget(UPrimitiveComponent* new_Target);
	void SetRotationTarget(UPrimitiveComponent* new_Target);

protected:	/**********************|    components    |**********************/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEmployeeState* State;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UEmplyeeThruser* Thrust;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	Flags_t flags;

public: // state api for external

	const UEmployeeState* GetState() const { return State; };
	const Flags_t& GetFlags() const { return flags; };

protected:	/**********************|    input vectors    |**********************/

	FVector LinearInput;
	FVector RotationInput;

public:

	void AddLinearInput(FVector input, bool bForce = false);
	void AddRotationInput(FVector input, bool bForce = false);

	FRotator GetControlRotation();

public:		/**********************|    overrides    |**********************/

	virtual void BeginPlay() override;
	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
protected:	/**********************|    update    |**********************/

	void UpdateInTargets(float DeltaTime);
	void UpdateSpeed_L(float DeltaTime);
	void UpdateSpeed_R(float DeltaTime);

	void UpdateTransforms(float DeltaTime);
};