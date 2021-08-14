#pragma once

#include "ECS/Entity.h"

#define UE_COMPONENT_INCREMENT_SLICE 128

namespace UE
{
	/* 
	* Position
	* Direction
	* Velocity
	* Sound
	* Name
	* Health
	* Mana
	* Inventory
	* XP
	* Brightness
	* Hunger
	* Thirst
	*/

	struct Component
	{
		float X[UE_MAX_ENTITIES];
		float Y[UE_MAX_ENTITIES];
		float Z[UE_MAX_ENTITIES];
	};
}