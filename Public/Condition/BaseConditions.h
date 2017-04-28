// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Condition/BaseConditions_base.h"
#include "Public/Condition/ResistanceTable.h"
#include "functional"


/*****************************************| Dinamic Component |*****************************************/
/**
*
*/

template<typename _BASE_CONDITIONS, typename _EFFECTS, int _CONDITIONS_COUNT, int _EFFECTS_COUNT>
class TROUNOIR_API UBaseConditions :
	public UBaseConditions_base<_BASE_CONDITIONS, _EFFECTS, _CONDITIONS_COUNT>,
	virtual public UResistanceTable<_EFFECTS, _EFFECTS_COUNT>
{
	typedef UBaseConditions_base<_BASE_CONDITIONS, _EFFECTS, _CONDITIONS_COUNT> Super;
	typedef UResistanceTable<_EFFECTS, _EFFECTS_COUNT>							Table;

public:
	UBaseConditions()
	{
		std::function<float(int, float)> foo = std::bind(&Table::PostResistanceResult, this, std::placeholders::_1, std::placeholders::_2);
		Super::UpdateCalculateEffectFunction(foo);
	}

	/*******************************| functions |*******************************/
public:

	void Tick(float DeltaSeconds)
	{
		Table::Tick(DeltaSeconds);
		Tick_internal(DeltaSeconds);
	}

	void Tick_internal(float DeltaSeconds)
	{
		Super::Tick(DeltaSeconds);
	}
};