// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
//#include "ConditionTypes.generated.h"


namespace ConditionsTypes {
	/**
	 * this namespace is set of, describeing states, enum
	 *
	 * CCS - core condinion states
	 * BCS - base conditon states
	 *
	 * for more information look in {} ConditonStates.h
	 */

	UENUM()
	enum CoreConditions
	{
		CCS_CONSTITUTION = 0,
		CCS_DEXTERITY,
		CCS_HARDENING,
		CCS_INTELLECT,

		CCS_COUNT
	};

	UENUM()
	enum BaseConditions
	{
		BCS_HEALTH = 0,
		BCS_STAMINA,
		BCS_REACTION,
		BCS_COORDINATION,
		BCS_SPEED,

		BCS_COUNT
	};
}