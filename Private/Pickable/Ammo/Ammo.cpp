// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"

#include "Public/Pickable/Ammo/Ammo.h"

#include "Engine.h"
#define MSG(N, TIME, TXT) GEngine->AddOnScreenDebugMessage(N, TIME, FColor::Yellow, (TXT))


AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent->OnComponentHit.AddDynamic(this, &AAmmo::OnHit);
	CapsuleComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	//CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetCapsuleSize(5,5);
	CapsuleComponent->bHiddenInGame = false;
	//CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//CapsuleComponent->SetCollisionProfileName("BlockAll");

	InitialEnergy = 1000 * 20;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 30*100;
	ProjectileMovement->MaxSpeed = 30*100;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;

	/*************/
	CalculateValues();
	/*************/

	Speed = ProjectileMovement->InitialSpeed;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovement->Activate();
	LastLocation = GetActorLocation();
}


void AAmmo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MSG(80, 1, GetActorLocation().ToCompactString());
	DrawDebugLine(
		GetWorld(),
		LastLocation,
		GetActorLocation(),
		FColor(200 * (Speed / ProjectileMovement->InitialSpeed),0,0),
		false, 60, 15, 1);
	LastLocation = GetActorLocation();
	Speed = ProjectileMovement->Velocity.Size();
}

FVector AAmmo::GetShootImpulse()
{ return -CapsuleComponent->GetMass() * GetProjectileMovement()->Velocity; }

void AAmmo::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MSG(80, 1, "impuct");

	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics()) {
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		Destroy();
	}
}


void AAmmo::PrintTrace()
{

}


/*****************************************************************|		EDITING		|*****************************************************************/

void AAmmo::PostInitProperties() 
{
	Super::PostInitProperties();

	CalculateValues();
}

#if WITH_EDITOR
void AAmmo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateValues();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void AAmmo::CalculateValues() 
{
	//ProjectileMovement->InitialSpeed = 30000;//FMath::Sqrt(2 * InitialEnergy / CapsuleComponent->GetMass());
}