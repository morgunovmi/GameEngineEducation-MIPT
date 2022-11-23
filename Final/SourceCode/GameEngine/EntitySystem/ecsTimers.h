#pragma once

#include "flecs.h"

struct ReloadTimer { float reloadTime; float elapsed; };
struct SelfDestroyTimer { float time; float elapsed; };

void register_ecs_timer_systems(flecs::world& ecs);