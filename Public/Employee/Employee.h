// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 main custom character class whith custom player controller
*/



#include "GameFramework/Pawn.h"
#include "Public/Employee/EmployeeController.h"
#include "Public/Condition/ConditionTypes.h"
#include "Public/Damage/DamageTypes.h"
#include "Employee.generated.h"

UCLASS()
class TROUNOIR_API AEmployee : public APawn
{
	GENERATED_BODY()

public:
	AEmployee();

protected:

	UEmployeeController* Controller;

	const UEmployeeController* GetController() const { return Controller; };

public:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* NewInputComponent) override;
	
protected:

	void AddLinearInput(FVector Ort, float Scale, bool bForce = false);
	//FVector GetMovementInputVector();

	void AddRotationInput(FRotator AdditionalInputRotator, bool bForce = false);
	//FRotator GetMovmentInputRotator();
};
