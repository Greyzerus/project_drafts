// Fill out your copyright notice in the Description page of Project Settings.

#include "TrouNoir.h"
#include "Public/Employee/EmployeeState.h"


UEmployeeState::UEmployeeState() :
	bIgnoreVectorInput(false),
	bIgnorRotatorInput(false),

	//floats
	bLS_Walk(200),
	bLS_Run(380),
	bLS_Sprint(580),

	bLA_Walk(100),
	bLA_Run(200),
	bLA_Sprint(300),

	bRS_Walk(50),
	bRS_Run(120),
	bRS_Sprint(180),

	bRA_Walk(50),
	bRA_Run(120),
	bRA_Sprint(180),

	bBA_Swim(200),
	bBA_Surface(300),
	bBA_Fly(400)
{
	SetMoveMode(IDLE);
	SetState(ST_SR_VERTICAL);
}


void UEmployeeState::SetMoveMode(MoveMode new_mode) {
	mode = new_mode;
}

typename MoveMode UEmployeeState::GetMoveMode() const {
	return mode;
}

typename GlobalState UEmployeeState::GetGlobalState() const {
	return g_state;
}

void UEmployeeState::SetState(State State) {
	state = State;

	if (state < 10) g_state = ON_SURFACE;
	else if (state < 20) g_state = ON_SWIMMING;
	else if (state < 30) g_state = ON_FLYING;
}

State UEmployeeState::GetState() const {
	return state;
}

float UEmployeeState::GetNormalAcceleration_L() const {
	switch (mode) {
	case IDLE:
	case SHIFTED:		return bLA_Walk;
	case NORMAL:		return bLA_Run;
	case SPRINTING:		return bLA_Sprint;
	default:			return -1;
	}
}

float UEmployeeState::GetNormalAcceleration_R() const {
	switch (mode) {
	case IDLE:
	case SHIFTED:		return bRA_Walk;
	case NORMAL:		return bRA_Run;
	case SPRINTING:		return bRA_Sprint;
	default:			return -1;
	}
}

float UEmployeeState::GetNormaltSpeed_L() const {
	switch (mode) {
	case IDLE:
	case SHIFTED:		return bLS_Walk;
	case NORMAL:		return bLS_Run;
	case SPRINTING:		return bLS_Sprint;
	default:			return -1;
	}
}

float UEmployeeState::GetNormaltSpeed_R() const {
	switch (mode) {
	case IDLE:
	case SHIFTED:		return bRS_Walk;
	case NORMAL:		return bRS_Run;
	case SPRINTING:		return bRS_Sprint;
	default:			return -1;
	}
}

float UEmployeeState::GetBrakeAcceleration_L() const {
	switch (g_state) {
	case ON_SURFACE:	return bBA_Surface;
	case ON_SWIMMING:	return bBA_Swim;
	case ON_FLYING:		return bBA_Fly;
	default:			return -1;
	}
}

float UEmployeeState::GetBrakeAcceleration_R() const {

	switch (mode) {
	case IDLE:
	case SHIFTED:		return bRA_Walk * 2;
	case NORMAL:		return bRA_Run * 2;
	case SPRINTING:		return bRA_Sprint * 2;
	default:			return -1;
	}
}