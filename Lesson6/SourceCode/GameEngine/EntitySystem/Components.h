#pragma once

#include <unordered_map>
#include <unordered_set>

#include "ecsMesh.h"
#include "ecsPhys.h"
#include "ecsGun.h"
#include "ecsScript.h"

enum EntityComponent {
	ePosition,
	eScale,
	eVelocity,
	eBouncePlane,
	eBounciness,
	eGravity,
	eFrictionAmount,
	eGun,
	eCubeMesh,
	eScripts
};

const std::unordered_map<std::string, EntityComponent> componentMap
{
	{"position", ePosition},
	{"scale", eScale},
	{"velocity", eVelocity},
	{"bounce_plane", eBouncePlane},
	{"bounciness", eBounciness},
	{"gravity", eGravity},
	{"friction_amount", eFrictionAmount},
	{"gun", eGun},
	{"cube_mesh", eCubeMesh},
	{"scripts", eScripts}
};

const std::unordered_map<std::string, std::unordered_set<EntityComponent>> sections
{
	{"transform", {ePosition, eScale}},
	{"physics", {eVelocity, eBouncePlane, eBounciness, eGravity, eFrictionAmount}}
};
