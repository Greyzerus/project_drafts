// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Engine.h"
#include "Public/Employee/Manager/Manager.h"

#define MSG(TIME, TXT) GEngine->AddOnScreenDebugMessage(0, TIME, FColor::Yellow, (TXT));
#define MSGN(PLASE,TIME, TXT) GEngine->AddOnScreenDebugMessage(PLASE, TIME, FColor::Yellow, (TXT));


/*****************************************************|    constructor    |*****************************************************/

AManager::AManager():
		bArmLength(300),

		bFirstCameraPitchMax(75),
		bFirstCameraPitchMin(-90),

		bThirdCameraPitchMax(45),
		bThirdCameraPitchMin(-45),

		bCameraMode(2),

		bMinCameraDistance(50),
		bMaxCameraDistance(500)
{
	PrimaryActorTick.bCanEverTick = true;

	//set_default_values();

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule component"));
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
	CapsuleComponent->SetCollisionProfileName(TEXT("BlockAll"));

	RootComponent = CapsuleComponent;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(RootComponent);

	SkeletMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletMeshComponent->SetupAttachment(RootComponent);
	FVector F = SkeletMeshComponent->GetPhysicsAngularVelocity();

	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoomComponent->SetupAttachment(RootComponent);
	CameraBoomComponent->TargetArmLength = bArmLength;

	FirstCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstCameraComponent->SetupAttachment(SkeletMeshComponent, TEXT("FirstCameraSocket"));
	FirstCameraComponent->bAutoActivate = true;

	ThirdCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	ThirdCameraComponent->SetupAttachment(CameraBoomComponent);
	ThirdCameraComponent->bAutoActivate = true;
}

void AManager::set_default_values() {
}

/*****************************************************|    begin play    |*****************************************************/

void AManager::BeginPlay() {
	Super::BeginPlay();

	SelectCamera(bCameraMode);

	Controller->Initialisate(CapsuleComponent, SkeletMeshComponent);

}

/*****************************************************|    tick    |*****************************************************/

void AManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

/*****************************************************|    update    |*****************************************************/
#pragma region

void AManager::PostInitProperties() {
	Super::PostInitProperties();

	CalculateValues();
}


#if WITH_EDITOR
void AManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	CalculateValues();

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif


void AManager::CalculateValues() {
	CameraBoomComponent->TargetArmLength = bArmLength;
	SelectCamera(bCameraMode);
}

#pragma endregion
/*****************************************************|    setup input    |*****************************************************/

void AManager::SetupPlayerInputComponent(class UInputComponent* NewInputComponent) {
	Super::SetupPlayerInputComponent(NewInputComponent);

	check(NewInputComponent);

	NewInputComponent->BindAction("ChangeView", IE_Pressed, this, &AManager::ChangeCamera);

	NewInputComponent->BindAction("MouseWheelUp", IE_Released, this, &AManager::MouseWheelUp);
	NewInputComponent->BindAction("MouseWheelDown", IE_Released, this, &AManager::MouseWheelDown);

	NewInputComponent->BindAction("Jump", IE_Pressed, this, &AManager::JumpPrepere);
	NewInputComponent->BindAction("Jump", IE_Released, this, &AManager::Jump);

	NewInputComponent->BindAction("Run", IE_Pressed, this, &AManager::DoRun);
	NewInputComponent->BindAction("Run", IE_Released, this, &AManager::DoWalk);

	NewInputComponent->BindAction("Sprint", IE_Pressed, this, &AManager::DoSprint);
	NewInputComponent->BindAction("Sprint", IE_Released, this, &AManager::DoWalk);



	NewInputComponent->BindAxis("LookYaw", this, &AManager::LookYaw);
	NewInputComponent->BindAxis("LookPitch", this, &AManager::LookPitch);

	NewInputComponent->BindAxis("MoveForward", this, &AManager::MoveForvard);
	NewInputComponent->BindAxis("MoveSide", this, &AManager::MoveSide);
}

/*****************************************************|    control    |*****************************************************/
/*camera*/
#pragma region

void AManager::ChangeCamera() {
	bCameraMode = bCameraMode == 2 ? 1 : 2;
	SelectCamera(bCameraMode);

	MSG(2, "changet to " + FString::SanitizeFloat(bCameraMode));
}

void AManager::SelectCamera(int N) {
	if (N == 1) {
		FirstCameraComponent->bIsActive = true;
		ThirdCameraComponent->bIsActive = false;
		bCameraMode = 1;
	}
	else if (N == 2) {
		FirstCameraComponent->bIsActive = false;
		ThirdCameraComponent->bIsActive = true;
		bCameraMode = 2;
	}
}

void AManager::MouseWheelUp() {
	switch (bCameraMode) {
	case 1:
		break;
	case 2:
		ChangeCameraDistance(1);
		break;
	}
	MSG(1, "MouseWheelUp");
}

void AManager::MouseWheelDown() 
{
	switch (bCameraMode) {
	case 1:
		break;
	case 2:
		ChangeCameraDistance(-1);
		break;
	}
}

void AManager::ChangeCameraDistance(int Val) 
{
	bArmLength = FMath::Clamp(bArmLength + Val*20.f, bMinCameraDistance, bMaxCameraDistance);
	CameraBoomComponent->TargetArmLength = bArmLength;
}


void AManager::LookYaw(float Val) 
{
	switch (bCameraMode) {
	case 1:
		break;
	case 2:
		FRotator CurrentRotation = CameraBoomComponent->GetComponentRotation();
		CurrentRotation.Yaw += Val;
		CurrentRotation.Roll = 0;
		CameraBoomComponent->SetWorldRotation(CurrentRotation);
		break;
	}
}

void AManager::LookPitch(float Val) 
{
	FRotator R;
	if (Val != 0.f)
		switch (bCameraMode) {
		case 1:

			break;
		case 2:
			FRotator CurrentRotation = CameraBoomComponent->GetComponentRotation();
			CurrentRotation.Pitch += Val;
			CurrentRotation.Roll = 0;
			CameraBoomComponent->SetWorldRotation(CurrentRotation);
			break;
		}
}

#pragma endregion

/*movement*/
#pragma region

void AManager::MoveForvard(float Val) 
{
	if (Val != 0)
		switch (bCameraMode) {
		case 1: {
			const FRotator Rotation = Controller->GetControlRotation();
			const FVector Direction = Rotation.Vector();
			AddLinearInput(Direction, Val);
			break;
		}
		case 2: {
			const FRotator Rotation = Controller->GetControlRotation();
			const FVector Direction = Rotation.Vector();
			AddLinearInput(Direction, Val);

			MSG(0.1, "move forvard");
			break;
		}
		}
}

void AManager::MoveSide(float Val) 
{
	if (Val != 0)
		switch (bCameraMode) {
		case 1: {
			const FRotator Rotation = Controller->GetControlRotation() + FRotator(0, 90, 0);
			const FVector Direction = Rotation.Vector();
			AddLinearInput(Direction, Val);
			break;
		}
		case 2: {
			const FRotator Rotation = Controller->GetControlRotation();
			const FVector Direction = Rotation.Vector();
			AddLinearInput(Direction, Val);
			break;
		}
		}
}

void AManager::Rotate(float Val) {
	SkeletMeshComponent->AddLocalRotation(FRotator(0, Val, 0));
}

void AManager::RotateToRotatior(FRotator Target, float time /*=0*/) {

}

void AManager::RotateToTarget(AActor Target, float time /*=0*/) {

}

void AManager::JumpPrepere() {

}

void AManager::Jump() {

}

void AManager::DoWalk() {

}

void AManager::DoRun() {

}

void AManager::DoSprint() {

}

#pragma endregion