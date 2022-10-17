#pragma once

#include "flecs.h"
#include <vector>
#include <string_view>

struct ScriptProxies
{
	std::vector<std::string> script_files;
};

void register_ecs_script_systems(flecs::world& ecs);
