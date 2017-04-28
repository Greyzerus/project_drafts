// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TrouNoir.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "TrouNoirCharacter.h"

#include "Engine.h"
#define MSG(N, TIME, TXT) GEngine->AddOnScreenDebugMessage(N, TIME, FColor::Yellow, (TXT))

float foo(const float l, const float r)
{ return r * 10; }

ATrouNoirCharacter::ATrouNoirCharacter() :
	states(),
	Gun(nullptr)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->AddLocalOffset(FVector());

	/*******************************************************************************************************************************************/

	/*******************************************************************************************************************************************/
	
	states.AddState(ConditionsTypes::CoreConditions::CCS_CONSTITUTION, DamageTypes::DamageType::DT_MAGIC, 30, 0);
	states.AddState(ConditionsTypes::CoreConditions::CCS_CONSTITUTION, DamageTypes::DamageType::DT_MAGIC, 10, 5, 0);
	states.AddState(ConditionsTypes::CoreConditions::CCS_CONSTITUTION, DamageTypes::DamageType::DT_MAGIC, &foo, 10, 0);


	states.AddState(ConditionsTypes::BaseConditions::BCS_HEALTH, DamageTypes::DamageType::DT_MAGIC, 100, 0);
	states.AddState(ConditionsTypes::BaseConditions::BCS_HEALTH, DamageTypes::DamageType::DT_MAGIC, 15, 8, 0);


	states.AddResistance(DamageTypes::DamageType::DT_MAGIC, 0.5, 0);
}


void ATrouNoirCharacter::Tick(float DeltaSeconds)
{
	states.Tick(DeltaSeconds);

	for (int i = ConditionsTypes::CoreConditions::CCS_COUNT - 1; i >= 0; --i)
		MSG(i, 0.1,			states.GetCoreStates().toString(i));
	MSG(29, 0.1, "------------------------");

	
	for (int i = ConditionsTypes::CoreConditions::CCS_COUNT - 1; i >= 0; --i)
		MSG(30 + i, 0.1,	states.GetBaseStates().toString(i));
	MSG(59, 0.1, "------------------------");
	

	if (Gun) { // print debug linear to Gun
		DrawDebugLine(
			GetWorld(), 
			GetMesh()->GetSocketLocation("RightHend"), 
			Gun->GetActorLocation(), FColor(125, 125, 0), false, 0.1, 15, 1);
	}
}


void ATrouNoirCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATrouNoirCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATrouNoirCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATrouNoirCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATrouNoirCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATrouNoirCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATrouNoirCharacter::TouchStopped);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATrouNoirCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ATrouNoirCharacter::Shoot);
	PlayerInputComponent->BindAction("E", IE_Pressed, this, &ATrouNoirCharacter::Interact);
}


void ATrouNoirCharacter::OnResetVR()
{ UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(); }

void ATrouNoirCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{ Jump(); }

void ATrouNoirCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{ StopJumping(); }

void ATrouNoirCharacter::TurnAtRate(float Rate)
{ AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); }

void ATrouNoirCharacter::LookUpAtRate(float Rate)
{ AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); }

void ATrouNoirCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATrouNoirCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ATrouNoirCharacter::Shoot()
{
	if (Gun) {
		Gun->Shoot();
		MSG(92, 15, FString::SanitizeFloat(sizeof(AWeapon)));
	}
}

void ATrouNoirCharacter::Interact()
{
	FHitResult HitData(ForceInit);
	FVector start = FollowCamera->GetComponentLocation();
	FVector end = start + FollowCamera->GetComponentRotation().Vector() * (CameraBoom->TargetArmLength + 300);
	GetWorld()->LineTraceSingleByChannel(HitData, start, end, ECollisionChannel::ECC_Visibility);

	AWeapon* tmp = Cast<AWeapon>(HitData.Actor.Get());
	if (tmp) {
		if (Gun) 
			Gun->Destroy();
		Gun = tmp;

		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "RightHend");

		MSG(60, 1, tmp->GetName());
		DrawDebugLine(GetWorld(), start, HitData.ImpactPoint, FColor(255, 0, 0), false, 5, 15, 1);
	}
}