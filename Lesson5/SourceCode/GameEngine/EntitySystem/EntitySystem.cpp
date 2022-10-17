#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ecsGun.h"
#include "ecsTimers.h"
#include "ecsScript.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, CScriptSystem* scriptSystem)
{
	ecs.entity("inputHandler")
		.set(InputHandlerPtr{ inputHandler });
	ecs.entity("renderEngine")
		.set(RenderEnginePtr{ renderEngine });
	ecs.entity("scriptSystem")
		.set(ScriptSystemPtr{ scriptSystem });

	auto bullet = ecs.prefab()
		.set(Position{ 0, 0, -100.f })
		.set(Velocity{ 0, 0, 0 })
		.set(Scale{ 0.5f })
		.set(BoundingBox{ 0.3f, 0.3f, 0.3f })
		.set(BouncePlane{ 0.f, 1.f, 0.f, -3.f })
		.set(DeathPlane{ 0.f, 1.f, 0.f, -3.f })
		.set(Bounciness{ 0.3f })
		.set(Gravity{ 0.f, -9.8065f, 0.f })
		.set(FrictionAmount{ 0.2f })
		.add<Bullet>();

	auto gun = ecs.entity()
		.set(Position{ 0.f, 0.f, 0.f })
		.set(Scale{ 1.0f })
		.set(Velocity{ 0.f, 0.f, 0.f })
		.set(FrictionAmount{ 0.95f })
		.set(Gravity{ 0.f, -9.8065f, 0.f })
		.set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
		.set(Bounciness{ 0.3f })
		.set(Gun{ bullet, 2.f, 6, 6, 20.f })
		.set(ScriptProxies{ {"../../../Assets/scripts/move.lua",
			"../../../Assets/scripts/shoot.lua"} })
		.add<CubeMesh>();

	auto target = ecs.prefab()
		.set(Position{ 0, 0, 0 })
		.set(Velocity{ 0, 0, 0 })
		.set(Scale{ 0.5f })
		.set(BouncePlane{ 0.f, 1.f, 0.f, -3.f })
		.set(Bounciness{ 0.5f })
		.set(BoundingBox{ 0.5f, 0.5f, 0.5f })
		.set(Target{ 2 });

	for (float x = -5.f; x <= 5.f; x += 5)
	{
		for (float z = 5.f; z <= 15.f; z += 3)
		{
			ecs.entity()
				.is_a(target)
				.add<CubeMesh>()
				.set(Position{ x, 0, z });
		}
	}

	register_ecs_mesh_systems(ecs);
	register_ecs_phys_systems(ecs);
	register_ecs_timer_systems(ecs);
	register_ecs_script_systems(ecs);
}

void EntitySystem::Update()
{
	ecs.progress();
}