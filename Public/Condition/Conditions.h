// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Condition/BaseConditions.h"
#include "Public/Condition/CoreConditions.h"


/*****************************************| Dinamic Component |*****************************************/
/**
*
*/

template<typename _CORE_CONDITIONS, typename _BASE_CONDITIONS, typename _EFFECTS, int _CORE_CONDITIONS_COUNT, int _BASE_CONDITIONS_COUNT, int _EFFECTS_COUNT>
class TROUNOIR_API UConditions :
	public UBaseConditions<_BASE_CONDITIONS, _EFFECTS, _BASE_CONDITIONS_COUNT, _EFFECTS_COUNT>,
	public UCoreConditions<_CORE_CONDITIONS, _EFFECTS, _CORE_CONDITIONS_COUNT, _EFFECTS_COUNT>
{
	typedef UBaseConditions<_BASE_CONDITIONS, _EFFECTS, _BASE_CONDITIONS_COUNT, _EFFECTS_COUNT> Base;
	typedef UCoreConditions<_CORE_CONDITIONS, _EFFECTS, _CORE_CONDITIONS_COUNT, _EFFECTS_COUNT> Core;

public:
	UConditions()
	{
		std::function<float(int, float)> foo = std::bind(&Table::PostResistanceResult, this, std::placeholders::_1, std::placeholders::_2);
		Base::Super::UpdateCalculateEffectFunction(foo);
		Core::Super::UpdateCalculateEffectFunction(foo);
	}

	/*******************************| functions |*******************************/
public:

	void Tick(float DeltaSeconds)
	{
		Table::Tick(DeltaSeconds);
		Base::Tick_internal(DeltaSeconds);
		Core::Tick_internal(DeltaSeconds);
	}

	/*******************************| base |*******************************/
public:

	void AddAllow(_BASE_CONDITIONS state, bool value)
	{ Base::AddAllow(state, value); }

	void AddCoreAllow(_BASE_CONDITIONS state, float value, float time)
	{ Base::AddAllow(state, value, time); }

public: /*************| value API |*************/

	void AddState(_BASE_CONDITIONS state, _EFFECTS type, float value, int8 bForce)
	{ Base::AddState(state, type, value, bForce); }

	// intime set
	void AddState(_BASE_CONDITIONS state, _EFFECTS type, float value, float time, int8 bForce)
	{ Base::AddState(state, type, value, time, bForce); }

	void AddState(_BASE_CONDITIONS state, _EFFECTS type, float(*value)(float, float), float time, int8 bForce)
	{ Base::AddState(state, type, value, time, bForce); }


	/*******************************| core |*******************************/
public: 

	void AddAllow(_CORE_CONDITIONS state, bool value)
	{ Core::AddAllow(state, value); }

	void AddCoreAllow(_CORE_CONDITIONS state, float value, float time)
	{ Core::AddAllow(state, value, time); }

public: /*************| value API |*************/

	void AddState(_CORE_CONDITIONS state, _EFFECTS type, float value, int8 bForce)
	{ Core::AddState(state, type, value, bForce); }

	// intime set
	void AddState(_CORE_CONDITIONS state, _EFFECTS type, float value, float time, int8 bForce)
	{ Core::AddState(state, type, value, time, bForce); }

	void AddState(_CORE_CONDITIONS state, _EFFECTS type, float(*value)(float, float), float time, int8 bForce)
	{ Core::AddState(state, type, value, time, bForce); }
};