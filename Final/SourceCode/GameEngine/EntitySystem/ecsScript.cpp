#include "ecsScript.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsGun.h"
#include "ecsMesh.h"
#include "ecsTimers.h"
#include "SoundSystem.h"
#include "../ScriptSystem/ScriptSystem.h"
#include "../ScriptSystem/ScriptProxy.h"
#include "../GameEngine/InputHandler.h"
#include "../Input.h"

#include "Log.h"

void register_ecs_script_systems(flecs::world& ecs)
{
    static auto scriptQuery = ecs.query<ScriptSystemPtr>();
    static auto inputQuery = ecs.query<InputHandlerPtr>();
	static auto soundQuery = ecs.query<SoundSystemPtr>();
    ecs.system<const ScriptProxies>()
        .each([&](flecs::entity e, const ScriptProxies& scriptProxies)
            {
				inputQuery.each([&](InputHandlerPtr& inputHandler)
					{
					scriptQuery.each([&](ScriptSystemPtr ss)
						{
							soundQuery.each([&](SoundSystemPtr soundSystem)
								{
									for (const auto& file : scriptProxies.script_files)
									{
										Log("Creating script from file {}\n", file.c_str());
										auto sp = ss.ptr->CreateProxy(file.c_str());

										auto& lua = sp->GetLua();

										lua.new_usertype<flecs::world>(
											"World",
											"CreateEntity", [](flecs::world& world) { return world.entity(); },
											"GetEntity", [](flecs::world& world, flecs::entity_t id) { return world.entity(id); },
											"GetEntityByName", [](flecs::world& world, const char* name) { return world.entity(name); }
										);
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
										lua.new_usertype<BouncePlane>(
											"BouncePlane",
											"x", &BouncePlane::x,
											"y", &BouncePlane::y,
											"z", &BouncePlane::z,
											"w", &BouncePlane::w
											);
										lua.new_usertype<std::bitset<eIC_Max>>(
											"KeyBitset",
											"Test", &std::bitset<eIC_Max>::test
											);
										lua["InputCommand"] = lua.create_table_with(
											"GoLeft", eIC_GoLeft,
											"GoRight", eIC_GoRight,
											"GoForward", eIC_GoForward,
											"GoBack", eIC_GoBack,
											"Jump", eIC_Jump,
											"Fire", eIC_Fire
										);
										lua.new_usertype<InputHandler>(
											"InputHandler",
											"GetInputState", &InputHandler::GetInputState
											);
										lua.new_usertype<SoundSystem>(
											"SoundSystem",
											"StartSound", &SoundSystem::StartSound,
											"StartMood", &SoundSystem::StartMood
											);
										lua.new_usertype<flecs::entity>(
											"Entity",
											"GetPosition", [](flecs::entity e) { return e.get<Position>(); },
											"SetPosition", [](flecs::entity e, float x, float y, float z) { e.set(Position{ x, y, z }); },
											"GetVelocity", [](flecs::entity e) { return e.get<Velocity>(); },
											"SetVelocity", [](flecs::entity e, float x, float y, float z) { e.set(Velocity{ x, y, z }); },
											"GetBouncePlane", [](flecs::entity e) { return e.get<BouncePlane>(); },
											"GetGun", [](flecs::entity e) { return e.get<Gun>(); },
											"IsA", [](flecs::entity e, flecs::entity p) { e.is_a(p); },
											"AddOctaMesh", [](flecs::entity e) { e.add<OctaMesh>(); },
											"AddReloadTimer", [](flecs::entity e, float time) { e.set(ReloadTimer{ time, 0.0f }); }
										);

										lua.new_usertype<Gun>(
											"Gun",
											"bullet", &Gun::bullet,
											"reloadTime", &Gun::reloadTime,
											"numRounds", &Gun::numRounds,
											"capacity", &Gun::capacity,
											"muzzleSpeed", &Gun::muzzleSpeed
											);

										lua["entityId"] = e.id();
										lua["inputHandler"] = std::ref(*inputHandler.ptr);
										lua["soundSystem"] = std::ref(*soundSystem.ptr);
										lua["world"] = std::ref(ecs);
									}

									e.remove<ScriptProxies>();
								});
						});
					});
			});
}
