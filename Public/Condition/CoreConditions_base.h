// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Condition/ConditionState.h"
#include "functional"


/*****************************************| Dinamic Component |*****************************************/
/**
 * 
 */

#pragma region

template<typename _CORE_CONDITIONS, typename _EFFECTS, int _CONDITIONS_COUNT>
class TROUNOIR_API UCoreConditions_base
{
public:	
	UCoreConditions_base()
	{ 
		UpdateCalculateEffectFunction([](int effect, float value) {
			return value;
		});
	}

	~UCoreConditions_base() = default;

	/*******************************| state members |*******************************/
protected:
	ConditionUtilites::TCoreStates<_CONDITIONS_COUNT> StaticStates; // states, static in time

	ConditionUtilites::TInTimeStates<_CONDITIONS_COUNT> IntimeStates; // effects collector

	ConditionUtilites::TCoreStates<_CONDITIONS_COUNT> DynamicStates; // dinamic values

	ConditionUtilites::TCoreStates<_CONDITIONS_COUNT> States; // result values

	/*******************************| functions |*******************************/
public:
	
	void Tick(float DeltaSeconds)
	{
		CountDinamicalStates(DeltaSeconds);
		UpdateStates();
	}

	/*******************************| API |*******************************/
public:  /*************| allow API |*************/
	
	void AddAllow(
		_CORE_CONDITIONS state,
		bool value)
	{ StaticStates.bClosed[state] = value; }

	void AddCoreAllow(
		_CORE_CONDITIONS state,
		float value,
		float time)
	{
		IntimeStates.allowEffects[state].Add(
			ConditionUtilites::TAllowInTimeEffect(value, time)
		);
	}

public: /*************| value API |*************/

	void AddState(
		_CORE_CONDITIONS state,
		_EFFECTS type,
		float value,
		int8 bForce)
	{
		if (States.bClosed[state] > bForce)
			return;
		StaticStates.states[state] += (*CalculateEffect)(type, value);
	}

	void AddState(
		_CORE_CONDITIONS state,
		_EFFECTS type,
		float value,
		float time,
		int8 bForce)
	{
		IntimeStates.staticEffects[state].Add(
			ConditionUtilites::TStaticInTimeEffect(type, value, time, bForce)
		);
	}

	void AddState(
		_CORE_CONDITIONS state,
		_EFFECTS type,
		float(*value)(float, float),
		float time,
		int8 bForce)
	{
		IntimeStates.dynamicEffects[state].Add(
			ConditionUtilites::TDynamicInTimeEffect(type, value, time, bForce)
		);
	}

protected: /*************| service |*************/

	void CountDinamicalStates(float DeltaSeconds)
	{
		DynamicStates.clear();

		for (int state = 0; state < _CONDITIONS_COUNT; ++state)
		{
			/* allows */
			int allows = 0;
			for (int i = 0; i < IntimeStates.allowEffects[state].Num(); ++i) {
				auto& effect = IntimeStates.allowEffects[state][i].effect;
				auto& left   = IntimeStates.allowEffects[state][i].leftTime;

				allows += effect;

				if (left -= DeltaSeconds <= 0)
					IntimeStates.allowEffects[state].RemoveAt(i--);
			}
			DynamicStates.bClosed[state] = FMath::Clamp((int)DynamicStates.bClosed[state] + allows, -128, 127); // TODO update current allows

			/* static */
			for (int i = 0; i < IntimeStates.staticEffects[state].Num(); ++i) {
				auto& type   = IntimeStates.staticEffects[state][i].effectType;
				auto& left   = IntimeStates.staticEffects[state][i].leftTime;
				auto& bForce = IntimeStates.staticEffects[state][i].bForce;
				auto& effect = IntimeStates.staticEffects[state][i].effect;

				if (bForce >= States.bClosed[state])
					DynamicStates.states[state] += (*CalculateEffect)(type, effect);

				left -= DeltaSeconds;
				if (left <= 0)
					IntimeStates.staticEffects[state].RemoveAt(i--);
			}

			/* dynamic */
			for (int i = 0; i < IntimeStates.dynamicEffects[state].Num(); ++i) {
				auto& type     = IntimeStates.dynamicEffects[state][i].effectType;
				auto& left     = IntimeStates.dynamicEffects[state][i].leftTime;
				auto& bForce   = IntimeStates.dynamicEffects[state][i].bForce;
				auto& effect   = IntimeStates.dynamicEffects[state][i].effect;
				auto& lastCall = IntimeStates.dynamicEffects[state][i].lastCall;

				auto currCall = lastCall + DeltaSeconds;
				float effectValue = 0;

				if (bForce >= States.bClosed[state])
					effectValue = effect(lastCall, currCall);
				DynamicStates.states[state] += (*CalculateEffect)(type, effectValue);

				left -= DeltaSeconds;
				lastCall = currCall;
				if (left <= 0)
					IntimeStates.dynamicEffects[state].RemoveAt(i--);
			}
		} // countDinamicalStates(float DeltaSeconds)
	}

protected:

	std::function<float(int ,float)>* CalculateEffect;

	void UpdateCalculateEffectFunction(std::function<float(int, float)> x)
	{
		if (CalculateEffect)
			delete CalculateEffect;
		CalculateEffect = new std::function<float(int, float)>(x);
	}

public:

	void UpdateStates()
	{ States = StaticStates + DynamicStates; }

	const ConditionUtilites::TCoreStates<_CONDITIONS_COUNT>& GetCoreStates()
	{ return States; }

	float operator[](_CORE_CONDITIONS state)
	{ return States.states[state]; }
};

#pragma endregion