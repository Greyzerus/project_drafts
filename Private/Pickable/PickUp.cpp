// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Pickable/PickUp.h"


APickUp::APickUp() :
	isPicked(false),
	weight(0),
	volume(0)
{
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	RootComponent = Base;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule component"));
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
	CapsuleComponent->SetupAttachment(Base);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComponent);
}

void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


bool APickUp::operator==(APickUp& rs)
{ return false; }

/*
bool ASubClassOfPickUp::operator == (ASubClassOfPickUp& other)
{
	//LOGIC
}*/