// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Array.h"


namespace ConditionUtilites {
	/*******************************| InTime States (allows) |*******************************/
#pragma region
	/**
	* the structure using for intime effects, putting on 'bClosed' filds des states
	*/

	USTRUCT()
	struct TAllowInTimeEffect
	{
		int8 effect;

		float leftTime;

	public:
		TAllowInTimeEffect(
			int8 effect,
			float time
		) :
			effect(effect),
			leftTime(time)
		{}
	};
#pragma endregion

	/*******************************| InTime States (values) |*******************************/
#pragma region
	/**
	* structures for explanation temporal effects
	* @_EFFECTS - enum of effects
	* @instigator - pointer on object, placed the effect
	* @damageType - subtype of effect
	* @leftTime - time in seconds, left for the modifer work. In case of <= 0 effect removes
	* @bForce - force apply of the effect (i.m. the effect ignors effect resistans)
	*/

	USTRUCT()
	struct TInTimeEffect_base
	{
		float leftTime;

		int8 effectType;

		int8 bForce;

	public:
		TInTimeEffect_base(
			int8 effectType,
			float time, 
			int8 bForce = 0
		) :
			effectType(effectType),
			leftTime(time),
			bForce(bForce)
		{}
	};

	/**
	 * @_EFFECTS - enum of effects
	 * @effect - functor, contains fucton, returnug srenght if effect:
	 *					float <strenght> effect (const float <last time>, const float <current time>)
	 */
	USTRUCT()
	struct TDynamicInTimeEffect : public TInTimeEffect_base
	{
		TFunction<float(const float, const float)> effect;

		float lastCall;

	public:
		TDynamicInTimeEffect(
			int8 effectType,
			float(*effect)(const float, const float), 
			float time,
			int8 bForce = 0
		) :
			TInTimeEffect_base(effectType, time, bForce),
			effect(effect),
			lastCall(0)
		{}
	};

	/**
	 * @effect - value of effect in second
	 */
	USTRUCT()
	struct TStaticInTimeEffect : public TInTimeEffect_base
	{
		float effect;

	public:
		TStaticInTimeEffect(
			int8 effectType,
			float effect,
			float time, 
			int8 bForce = 0
		) :
			TInTimeEffect_base(effectType, time, bForce),
			effect(effect)
		{}
	};
#pragma endregion

	/*******************************| InTime States |*******************************/
#pragma region
	/**
	 * structure, agregating intime effects
	 * @_EFFECTS - enum of effects
	 * @_SIZE - count of states
	 */

	USTRUCT()
	struct TInTimeStates
	{
		TArray<
			TArray<
				TStaticInTimeEffect>> staticEffects;
		TArray<
			TArray<
				TDynamicInTimeEffect>> dynamicEffects;
		TArray<
			TArray<
				TAllowInTimeEffect>> allowEffects;
	public:
		TInTimeStates(int ConditionsCount)
		{
			staticEffects.Reserve	(ConditionsCount);
			dynamicEffects.Reserve	(ConditionsCount);
			allowEffects.Reserve	(ConditionsCount);
			for (int i = 0; i < ConditionsCount; ++i) {
				staticEffects.Emplace();
				dynamicEffects.Emplace();
				allowEffects.Emplace();
			}
		}
	};
#pragma endregion

	/*******************************| Core States |*******************************/
#pragma region
	/**
	* semiabstract structure,																			//TODO description
	* .core states doesn't have 'healling'
	* @_SIZE - count of states
	* @states - values of states
	* @bForce - flag of force update: if updatee has it 1 but updater 0, so update wont be done
	*/

	USTRUCT()
	struct TCoreStates
	{
	protected:
		const static int8  AllowMin = -125;
		const static int8  AllowMax =  125;
		const static float StateMin = INT32_MIN;
		const static float StateMax = INT32_MAX;

	public:
		int count;

		TArray<float> states;

		TArray<int8> bClosed;

	public:
		TCoreStates(int Size) :
			count(Size)
		{
			states.Reserve	(Size);
			bClosed.Reserve	(Size);
			for (int i = 0; i < Size; ++i) {
				states.Emplace();
				bClosed.Emplace(); 
			}
		}

		void clear()
		{
			int max = states.Num();
			for (int i = 0; i < max; ++i) {
				states[i] = 0;
				bClosed[i] = 0; 
			}
		}

	public:
		TCoreStates operator+(const TCoreStates& rs) const
		{
			if (rs.count >= count)
				TCoreStates tmp(rs);
			else
				TCoreStates tmp(*this);
			int max = FMath::Min(rs.states.Num(), this->states.Num());
			for (int i = 0; i < max; ++i) {
				tmp.states[i]  += rs.states[i];
				tmp.bClosed[i] += rs.bClosed[i];
			} return tmp;
		}

		TCoreStates ClampedSum(const TCoreStates& rs, const TCoreStates limiter) const
		{
			TCoreStates tmp(*this);
			int max = FMath::Min3(rs.states.Num(), limiter.states.Num(), this->states.Num());
			for (int i = 0; i < max; ++i) {
				tmp.states[i]  = FMath::Clamp(tmp.states[i]  + rs.states[i],  StateMin, limiter.states[i]);
				tmp.bClosed[i] = FMath::Clamp(tmp.bClosed[i] + rs.bClosed[i], AllowMin, limiter.bClosed[i]);
			} return tmp;
		}

		FString toString(int i) const
		{ return FString::SanitizeFloat(states[i]) + "    " + (bClosed[i] ? "true" : "false"); }
	};
#pragma endregion

	/*******************************| Resistance Table + component |*******************************/
#pragma region
	
#pragma endregion












} // namespace ConditionUtilites