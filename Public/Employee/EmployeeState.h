// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "EmployeeState.generated.h"


UENUM(BlueprintType)
enum MoveMode {
	IDLE,
	NORMAL,		//run
	SHIFTED,	//walk
	SPRINTING
};


UENUM(BlueprintType)
enum GlobalState {
	ON_SURFACE,
	ON_SWIMMING,
	ON_FLYING
};

UENUM(BlueprintType)
enum State {
	ST_SR_VERTICAL = 0,
	ST_SR_BALANCEING = 1,
	ST_SR_OVERTURNING = 2,
	ST_SR_LYING = 3,

	ST_SW_SURFACE = 10,
	ST_SW_SUB_SURFACE = 11,

	ST_FL_FALLING = 20,
	ST_FL_FLYING = 21
};


/**
* common state machine class for employee movememnt controller
*
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TROUNOIR_API UEmployeeState : public UObject
{
	GENERATED_BODY()

public:	

	UEmployeeState();

public:
	// move state
	void SetMoveMode(MoveMode new_mode);
	MoveMode GetMoveMode() const;

	// global state
	GlobalState GetGlobalState() const;

	// state
	void SetState(State new_state);
	State GetState() const;

public: // L - linear ; R - rotation
	// upspeed
	float GetNormalAcceleration_L() const;
	float GetNormalAcceleration_R() const;

	float GetNormaltSpeed_L() const;
	float GetNormaltSpeed_R() const;

	// brake
	float GetBrakeAcceleration_L() const;
	float GetBrakeAcceleration_R() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Main", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<MoveMode> mode;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Main", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<GlobalState> g_state;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Main", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<State> state;

public: /**************************************************|    bool flags    |**************************************************/

	bool bIgnoreVectorInput;

	bool bIgnorRotatorInput;

protected: /**************************************************|    float parametrs    |**************************************************/

		   // linear speed (LS_)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Walk", meta = (AllowPrivateAccess = "true"))
	float bLS_Walk;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Run", meta = (AllowPrivateAccess = "true"))
	float bLS_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float bLS_Sprint;

			// linear acceleration (LA_)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Walk", meta = (AllowPrivateAccess = "true"))
	float bLA_Walk;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Run", meta = (AllowPrivateAccess = "true"))
	float bLA_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float bLA_Sprint;


		// rotation speed (RS_)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Walk", meta = (AllowPrivateAccess = "true"))
	float bRS_Walk;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Run", meta = (AllowPrivateAccess = "true"))
	float bRS_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float bRS_Sprint;

			// rotation acceleration (RA_)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Walk", meta = (AllowPrivateAccess = "true"))
	float bRA_Walk;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Run", meta = (AllowPrivateAccess = "true"))
	float bRA_Run;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprint", meta = (AllowPrivateAccess = "true"))
	float bRA_Sprint;

			//brake accelearation (BA_)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Swim", meta = (AllowPrivateAccess = "true"))
	float bBA_Swim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Surafce", meta = (AllowPrivateAccess = "true"))
	float bBA_Surface;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fly", meta = (AllowPrivateAccess = "true"))
	float bBA_Fly;

};
