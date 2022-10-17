#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../ScriptSystem/ScriptSystem.h"
#include "../InputHandler.h"

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptSystem* scriptSystem);

	void Update();
private:
	flecs::world ecs;
	uint16_t m_maxPlaceholders = 50;
};

