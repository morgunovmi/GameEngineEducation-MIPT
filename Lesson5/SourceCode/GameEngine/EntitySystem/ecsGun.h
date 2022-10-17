#pragma once

#include "flecs.h"

struct Placeholder { };

struct Gun
{
	flecs::entity bullet; float reloadTime; uint16_t numRounds; uint16_t capacity; float muzzleSpeed;
};

struct Bullet { };

struct Target { uint16_t bonus; };