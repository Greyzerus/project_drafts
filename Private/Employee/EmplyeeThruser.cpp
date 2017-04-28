// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Employee/EmplyeeThruser.h"


UEmplyeeThruser::UEmplyeeThruser():
		IsInitialisated(false)
{
	PrimaryComponentTick.bCanEverTick = false;

	MainThrust = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Main Thruster"));
	MainThrust->ThrustStrength = 0;
	MainThrust->bAutoActivate = true;

	TopThrust_P = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Top Pitch Thruster"));
	TopThrust_P->ThrustStrength = 0;
	TopThrust_P->bAutoActivate = true;

	BottomThrust_P = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Bottom Pitch Thruster"));
	BottomThrust_P->ThrustStrength = 0;
	BottomThrust_P->bAutoActivate = true;

	LeftThrust_Y = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Left Yaw Thruster"));
	LeftThrust_Y->ThrustStrength = 0;
	LeftThrust_Y->bAutoActivate = true;

	RightThrust_Y = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Right Yaw Thruster"));
	RightThrust_Y->ThrustStrength = 0;
	RightThrust_Y->bAutoActivate = true;

	TopThrust_R = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Top Roll Thruster"));
	TopThrust_R->ThrustStrength = 0;
	TopThrust_R->bAutoActivate = true;

	BottomThrust_R = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Bottom Roll Thruster"));
	BottomThrust_R->ThrustStrength = 0;
	BottomThrust_R->bAutoActivate = true;
}


void UEmplyeeThruser::BeginPlay()
{
	Super::BeginPlay();

	
}


void UEmplyeeThruser::Inicialisate(UPrimitiveComponent* NewRotationTarget, UPrimitiveComponent* NewLocationTarget) {

	if (NewLocationTarget == nullptr)
		return;

	MainThrust->AttachTo(NewLocationTarget);

	if (NewRotationTarget == nullptr)
		return;

	IsInitialisated = true;

	TopThrust_P->SetupAttachment(NewRotationTarget);
	TopThrust_P->SetRelativeLocation(FVector(0, 0, 100));

	BottomThrust_P->SetupAttachment(NewRotationTarget);
	BottomThrust_P->SetRelativeLocation(FVector(0, 0, -100));
	BottomThrust_P->SetRelativeRotation(FRotator(0, 180, 0));


	LeftThrust_Y->SetupAttachment(NewRotationTarget);
	LeftThrust_Y->SetRelativeLocation(FVector(0, 100, 0));
	LeftThrust_Y->SetRelativeRotation(FRotator(0, 180, 0));

	RightThrust_Y->SetupAttachment(NewRotationTarget);
	RightThrust_Y->SetRelativeLocation(FVector(0, -100, 0));


	TopThrust_R->SetupAttachment(NewRotationTarget);
	TopThrust_R->SetRelativeLocation(FVector(0, 0, 100));
	TopThrust_R->SetRelativeRotation(FRotator(0, 90, 0));

	BottomThrust_R->SetupAttachment(NewRotationTarget);
	BottomThrust_R->SetRelativeLocation(FVector(0, 0, -100));
	BottomThrust_R->SetRelativeRotation(FRotator(0, -90, 0));
}

#include "Engine.h"
#define MSG(TIME, TXT) GEngine->AddOnScreenDebugMessage(1, TIME, FColor::Red, (TXT));

void UEmplyeeThruser::AddLinearForce(FVector new_Force) {

	if (!IsInitialisated)
		return;

	MainThrust->SetRelativeRotation(new_Force.ToOrientationRotator());
	MainThrust->ThrustStrength = -new_Force.Size();

	MSG(0.1, "move forvard " + new_Force.ToCompactString() + " " + MainThrust->RelativeRotation.ToCompactString() + " ");
}

void UEmplyeeThruser::AddRotationForce(FRotator &new_Force) {

	if (!IsInitialisated)
		return;

}