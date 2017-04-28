// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "DamageTypes.generated.h"

namespace DamageTypes
{
	/**
	 * this namespace is set of enums, describeing 
	 * damage types or, if you wish,* types of all effects
	 *
	 * the effects describes only here and modules,
	 * useing them, must use the unum in their logic			// TODO study english
	 *
	 * DTG - global damage types 
	 * DT - subtypes of damage
	 */


	UENUM()
	enum DamageType_global
	{
		DTG_CLEAR = 0,
		DTG_PHYSICAL,
		DTG_POISON,

		DTG_COUNT // !!!! this is the last element in the enum
	};

	UENUM()
	enum DamageType
	{
		DT_CLEAR = 0,
		DT_PHYSICAL,
		DT_MAGIC,

		DT_COUNT // !!!! this is the last element in the enum
	};


} // namespace DamageTypes