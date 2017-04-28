// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Condition/CoreConditions_common.h"

template<typename _EFFECTS, int _EFFECTS_COUNT>
class TROUNOIR_API UResistanceTable
{
protected:

	UCoreConditions_common<_EFFECTS, _EFFECTS_COUNT> table;
	// add a shift table

public:

	float PostResistanceResult(int effect, float value)
	{
		// do logic for a shift
		return value * (1 - table.GetCoreStates().states[effect]);
	}

	void Tick(float DeltaSeconds)
	{
		table.Tick(DeltaSeconds);
	}

public: /*************| resistance API |*************/
	/* value API */

	void AddResistance(
		_EFFECTS effect,
		float value,
		int8 bForce)
	{ table.AddState(effect, value, bForce); }

	void AddResistance(
		_EFFECTS effect,
		float value,
		float time,
		int8 bForce)
	{ table.AddState(effect, value, time, bForce); }

	void AddResistance(
		_EFFECTS effect,
		float(*value)(float, float),
		float time,
		int8 bForce)
	{ table.AddState(effect, value, time, bForce); }

	/* allows API */

	void AddResistanceAllow(
		_EFFECTS effect,
		bool value)
	{ table.AddAllow(effect, value); }

	void AddResistanceAllow(
		_EFFECTS effect,
		float value,
		float time)
	{ table.AddAllow(effect, value, time); }
};
