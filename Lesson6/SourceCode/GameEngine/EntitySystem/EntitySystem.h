#pragma once

#include <string_view>

#include "flecs.h"
#include "RenderEngine.h"
#include "../ScriptSystem/ScriptSystem.h"
#include "../InputHandler.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptSystem* scriptSystem, std::string_view world_file);

	void Update();
private:
	flecs::world ecs;
};

