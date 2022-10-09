#pragma once

#include <flecs.h>

struct Placeholder{ };

struct Gun
{
	flecs::entity bullet; uint16_t num_rounds;
};

struct Bullet { };
