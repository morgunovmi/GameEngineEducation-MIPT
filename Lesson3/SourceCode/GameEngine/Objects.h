#pragma once

#include "RoamingCubeGameObject.h"
#include "JumpingCubeGameObject.h"
#include "ControllableCubeGameObject.h"

enum EObjectType : size_t
{
	eOT_Roaming = 0,
	eOT_Jumping,
	eOT_Controllable,

	eOT_Max
};
