// Fill out your copyright notice in the Description page of Project Settings.

/*
"void UCoreConditions_base<_CORE_CONDITIONS,_EFFECTS,4>::UpdateCalculateEffectFunction(std::function<float (int,float)>)":

"std::_Binder<std::_Unforced,float (__cdecl UResistanceTable<_EFFECTS,3>::* )(_EFFECTS,float),UCoreConditions<ConditionsTypes::CoreConditions,_EFFECTS,4,3> *const ,const std::_Ph<1> &,const std::_Ph<2> &>"

"std::function<float (int,float)>"

*/


#pragma once

#include "Public/Condition/CoreConditions_base.h"
#include "Public/Condition/ResistanceTable.h"


 /*****************************************| Dinamic Component |*****************************************/
 /**
 * 
 */

template<typename _CORE_CONDITIONS, typename _EFFECTS, int _CONDITIONS_COUNT, int _EFFECTS_COUNT>
class TROUNOIR_API UCoreConditions : 
	public UCoreConditions_base<_CORE_CONDITIONS, _EFFECTS, _CONDITIONS_COUNT>,
	virtual public UResistanceTable<_EFFECTS, _EFFECTS_COUNT>
{
	typedef UCoreConditions_base<_CORE_CONDITIONS, _EFFECTS, _CONDITIONS_COUNT> Super;
	typedef UResistanceTable<_EFFECTS, _EFFECTS_COUNT>							Table;

public:
	UCoreConditions()
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
