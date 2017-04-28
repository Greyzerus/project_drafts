// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Employee/EmployeeController.h"


UEmployeeController::UEmployeeController() :
		IsInitializated(false)
{
	PrimaryComponentTick.bCanEverTick = true;
	State = CreateDefaultSubobject<UEmployeeState>(TEXT("State"));
	Thrust = CreateDefaultSubobject<UEmplyeeThruser>(TEXT("Thrust"));
}


		/**********************|    targets    |**********************/

void UEmployeeController::Initialisate(UPrimitiveComponent* new_LocationTarget, UPrimitiveComponent* new_RotationTarget) 
{
	SetLocationTarget(new_LocationTarget);
	SetRotationTarget(new_RotationTarget);
	Thrust->Inicialisate(new_RotationTarget, new_LocationTarget);
	IsInitializated = true;
}


void UEmployeeController::SetLocationTarget(UPrimitiveComponent* new_Target) 
{
	if (new_Target == nullptr)  // TODO: send smg to log
		return;

	LocationTarget = new_Target;
}


void UEmployeeController::SetRotationTarget(UPrimitiveComponent* new_Target) 
{
	if (new_Target == nullptr) // TODO: send smg to log
		return;

	RotationTarget = new_Target;
}


		/**********************|    input vectors    |**********************/

void UEmployeeController::AddLinearInput(FVector input, bool bForce/* = false*/)
{
	if ((flags.bLI_ignore ^ bForce) == 1)
		return;
	LinearInput += input;
}


void UEmployeeController::AddRotationInput(FVector input, bool bForce/* = false*/) 
{
	if ((flags.bLI_ignore ^ bForce) == 1)
		return;

	RotationInput += input;
}


FRotator UEmployeeController::GetControlRotation() 
{
	return RotationTarget->GetComponentRotation() + RotationTarget->RelativeRotation;
}

		/**********************|    overrides    |**********************/

void UEmployeeController::BeginPlay() 
{
	Super::BeginPlay();

}


void UEmployeeController::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) 
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!IsInitializated)
		return;

	UpdateInTargets(DeltaTime);
}


		/**********************|    update    |**********************/

void UEmployeeController::UpdateInTargets(float DeltaTime) 
{
	UpdateSpeed_L(DeltaTime);
	UpdateSpeed_R(DeltaTime);
}

#include "Engine.h"
#define MSG(TIME, TXT) GEngine->AddOnScreenDebugMessage(0, TIME, FColor::Yellow, (TXT));

void UEmployeeController::UpdateSpeed_L(float DeltaTime) 
{
	FVector speed = LocationTarget->ComponentVelocity;
	FVector Force;
	float Mass = LocationTarget->GetMass();

	if (speed.Size() > GetState()->GetNormaltSpeed_L()) {
		Force = Mass * LinearInput * GetState()->GetBrakeAcceleration_L() / DeltaTime;
		Thrust->AddLinearForce(Force);
	}
	else {
		Force = Mass * LinearInput * GetState()->GetNormalAcceleration_L() / DeltaTime;
		Thrust->AddLinearForce(Force);

	}
	MSG(0.1, "move forvard " + Force.ToCompactString());
	LinearInput = FVector::ZeroVector;
}


void UEmployeeController::UpdateSpeed_R(float DeltaTime) 
{
	
}