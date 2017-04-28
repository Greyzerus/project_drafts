// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Employee/Employee.h"
#include "Manager.generated.h"


/**
 * gameplay character
 */
UCLASS()
class TROUNOIR_API AManager : public AEmployee
{
	GENERATED_BODY()
	
	void set_default_values();
public:

	AManager();

public:		/**************************************************|    components    |*****************************************************/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletMeshComponent;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComponent;

public:		/**************************************************|    values    |*****************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bThirdCameraPitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bThirdCameraPitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bFirstCameraPitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bFirstCameraPitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	int bCameraMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bMinCameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float bMaxCameraDistance;


public:		/*****************************************************|    *    |*****************************************************/

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitProperties() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual void CalculateValues();

	virtual void SetupPlayerInputComponent(class UInputComponent* NewInputComponent) override;

public:		/*****************************************************|    control    |*****************************************************/
		// /*camera*/
	void ChangeCamera();

	void SelectCamera(int N);

	void MouseWheelUp();

	void MouseWheelDown();

	void ChangeCameraDistance(int Val);

	void LookYaw(float Val);

	void LookPitch(float Val);

	// /*movement*/
	void MoveForvard(float Val);

	void MoveSide(float Val);

	void Rotate(float Val);

	void RotateToRotatior(FRotator Target, float time = 0);

	void RotateToTarget(AActor Target, float time = 0);

	void JumpPrepere();

	void Jump();

	void DoWalk();

	void DoRun();

	void DoSprint();
};
