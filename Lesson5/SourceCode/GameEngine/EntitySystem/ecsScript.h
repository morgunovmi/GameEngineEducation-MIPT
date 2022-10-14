#pragma once

#include "flecs.h"
#include <string_view>

struct ScriptProxy
{
	std::string_view script_file;
};

struct ScriptProxyPtr
{
	class IScriptProxy* ptr;
};

void register_ecs_script_systems(flecs::world& ecs);
