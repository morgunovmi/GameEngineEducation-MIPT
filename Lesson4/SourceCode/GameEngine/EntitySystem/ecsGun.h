#pragma once

#include "flecs.h"

struct Placeholder { };

struct Gun
{
	flecs::entity bullet; uint16_t numRounds; uint16_t capacity;
};

struct Bullet { };

struct Target { uint16_t bonus; };