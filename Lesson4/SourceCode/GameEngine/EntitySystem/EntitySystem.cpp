#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "ecsGun.h"
#include "ecsTimers.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

	auto bullet = ecs.prefab()
		.set(Position{ 0, 0, -100.f })
		.set(Velocity{ 0, 0, 0 })
		.set(Scale{ 0.5f })
		.set(BoundingBox{ 0.3, 0.3, 0.3 })
		.set(BouncePlane{ 0.f, 1.f, 0.f, -3.f })
		.set(DeathPlane{ 0.f, 1.f, 0.f, -3.f })
		.set(Bounciness{ 0.3f })
		.set(Gravity{ 0.f, -9.8065f, 0.f })
		.set(FrictionAmount{ 0.2f })
		.add<Bullet>();

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
		ecs.entity()
			.is_a(target)
			.add<CubeMesh>()
			.set(Position{ x, 0, 5 });
	}

	for (std::size_t i = 0; i < m_maxPlaceholders; ++i)
	{
		ecs.entity().add<Placeholder>();
	}

	auto gun = ecs.entity()
		.set(Position{ 0.f, 0.f, 0.f })
		.set(Scale{ 1.0f })
		.set(Velocity{ 0.f, 0.f, 0.f })
		.set(Speed{ 10.f })
		.set(FrictionAmount{ 0.9f })
		.set(JumpSpeed{ 10.f })
		.set(Gravity{ 0.f, -9.8065f, 0.f })
		.set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
		.set(Bounciness{ 0.3f })
		.set(Gun{ bullet, 6, 6 })
		.add<Controllable>()
		.add<CubeMesh>();

	register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
	register_ecs_timer_systems(ecs);
}

void EntitySystem::Update()
{
	static auto placeholderQuery = ecs.query<Placeholder>();
    ecs.progress();
	uint16_t count = 0;
	placeholderQuery.each([&](Placeholder&) { ++count; });
	for (uint16_t i = count; i < m_maxPlaceholders; ++i)
	{
		ecs.entity().add<Placeholder>();
	}
}