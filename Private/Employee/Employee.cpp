// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Employee/Employee.h"


AEmployee::AEmployee()
{
	PrimaryActorTick.bCanEverTick = true;

	Controller = CreateDefaultSubobject<UEmployeeController>("Controller");
}

void AEmployee::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEmployee::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEmployee::SetupPlayerInputComponent(class UInputComponent* NewInputComponent)
{
	Super::SetupPlayerInputComponent(NewInputComponent);

}

void AEmployee::AddLinearInput(FVector Ort, float Scale, bool bForce) {

	if (Controller) {
		Controller->AddLinearInput(Ort * Scale, bForce);
	}
}