// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Condition/CoreConditions_base.h"



/*****************************************| Dinamic Component |*****************************************/
/**
* 
*/

template<typename _CORE_CONDITIONS, int _CONDITIONS_COUNT>
class TROUNOIR_API UCoreConditions_common : 
	public UCoreConditions_base<_CORE_CONDITIONS, int, _CONDITIONS_COUNT>
{
	typedef UCoreConditions_base<_CORE_CONDITIONS, int, _CONDITIONS_COUNT> Super;

	/*******************************| API |*******************************/
public: /*************| value API |*************/

	void AddState(
		_CORE_CONDITIONS state,
		float value,
		int8 bForce)
	{ Super::AddState(state, 0, value, bForce); }

	void AddState(
		_CORE_CONDITIONS state,
		float value,
		float time,
		int8 bForce)
	{ Super::AddState(state, 0, value, time, bForce); }

	void AddState(
		_CORE_CONDITIONS state,
		float(*value)(float, float),
		float time,
		int8 bForce)
	{ Super::AddState(state, 0, value, time, bForce); }

};