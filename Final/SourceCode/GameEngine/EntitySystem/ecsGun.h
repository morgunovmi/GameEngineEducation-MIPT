#pragma once

#include "flecs.h"
#include <string>

struct Placeholder { };

struct Gun
{
	std::string bullet; float reloadTime; uint16_t numRounds; uint16_t capacity; float muzzleSpeed;
};

struct Bullet { };

struct Target { uint16_t bonus; };