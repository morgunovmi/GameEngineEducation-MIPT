#include "ecsScript.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "../ScriptSystem/ScriptSystem.h"
#include "../ScriptSystem/ScriptProxy.h"
#include "../GameEngine/InputHandler.h"
#include "../Input.h"

#include "Log.h"

void initialize_script(std::shared_ptr<CScriptProxy> proxy, flecs::world& ecs,
                       flecs::entity_t id, InputHandler* inputHandlerPtr)
{
    auto& lua = proxy->GetLua();

	lua.new_usertype<Position>(
		"Position",
		"x", &Position::x,
		"y", &Position::y,
		"z", &Position::z
		);
	lua.new_usertype<Velocity>(
		"Position",
		"x", &Velocity::x,
		"y", &Velocity::y,
		"z", &Velocity::z
		);
	lua.new_usertype<std::bitset<eIC_Max>>(
		"KeyBitset",
		"test", &std::bitset<eIC_Max>::test
		);
	lua.new_enum(
		"InputCommand",
		"GoLeft", eIC_GoLeft,
		"GoRight", eIC_GoRight,
		"Jump", eIC_Jump
	);
	lua.new_usertype<InputHandler>(
		"InputHandler",
		"getInputState", &InputHandler::GetInputState
		);

	lua["entity_id"] = id;
	lua["input_handler"] = std::ref(*inputHandlerPtr);
}

void register_ecs_script_systems(flecs::world& ecs)
{
    static auto scriptQuery = ecs.query<ScriptSystemPtr>();
    static auto inputQuery = ecs.query<InputHandlerPtr>();
    ecs.system<const ScriptProxy>()
        .each([&](flecs::entity e, const ScriptProxy& scriptProxy)
            {
				inputQuery.each([&](InputHandlerPtr& inputHandler) {
					scriptQuery.each([&](ScriptSystemPtr ss)
						{
							auto id = e.id();
							LogZA("Creating script\n");
							auto sp = ss.ptr->CreateProxy(scriptProxy.script_file.data());
							initialize_script(sp, ecs, e.id(), inputHandler.ptr);

							e.set(ScriptProxyPtr{ sp.get() });
							e.remove<ScriptProxy>();
						});
					});
			});
}
