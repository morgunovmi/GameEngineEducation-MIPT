#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsGun.h"
#include "ecsMesh.h"
#include "ecsTimers.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_control_systems(flecs::world& ecs)
{
	static auto inputQuery = ecs.query<InputHandlerPtr>();
	static auto placeholderQuery = ecs.query<Placeholder>();
	ecs.system<Velocity, const Speed, const Controllable>()
		.each([&](flecs::entity e, Velocity& vel, const Speed& spd, const Controllable&)
			{
				inputQuery.each([&](InputHandlerPtr input)
					{
						float deltaVel[3] = { 0.f, 0.f, 0.f };
						if (input.ptr->GetInputState().test(eIC_GoLeft))
							deltaVel[0] -= spd;
						if (input.ptr->GetInputState().test(eIC_GoRight))
							deltaVel[0] += spd;
						if (input.ptr->GetInputState().test(eIC_GoForward))
							deltaVel[2] += spd;
						if (input.ptr->GetInputState().test(eIC_GoBack))
							deltaVel[2] -= spd;
						vel.x += deltaVel[0] * e.delta_time();
						vel.z += deltaVel[2] * e.delta_time();
					});
			});

	ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
		.each([&](const Position& pos, Velocity& vel, const Controllable&, const BouncePlane& plane, const JumpSpeed& jump)
			{
				inputQuery.each([&](InputHandlerPtr input)
					{
						constexpr float planeEpsilon = 0.1f;
						if (plane.x * pos.x + plane.y * pos.y + plane.z * pos.z < plane.w + planeEpsilon)
							if (input.ptr->GetInputState().test(eIC_Jump))
								vel.y = jump.val;
					});
			});

	static bool shot_happened = false;
	ecs.system<const Position, const Velocity, Gun>()
		.each([&](flecs::entity e, const Position& pos, const Velocity& vel, Gun& gun)
			{
				inputQuery.each([&](flecs::entity inputEntity, InputHandlerPtr input)
					{
						if (input.ptr->GetInputState().test(eIC_Fire) && !shot_happened && gun.numRounds > 0)
						{
							bool spawned = false;
							placeholderQuery.each([&](flecs::entity placeholder, Placeholder&)
								{
									if (!spawned)
									{
										placeholder.mut(e)
											.is_a(gun.bullet)
											.set(Velocity{ vel.x, vel.y, vel.z + 30.f })
											.set(Position{ pos.x, pos.y, pos.z })
											.add<OctaMesh>()
											.remove<Placeholder>();

										spawned = true;
									}
								});
							shot_happened = true;
							--gun.numRounds;
							if (gun.numRounds == 0)
							{
								e.set(ReloadTimer{5, 0});
							}
						}
						else
						{
							shot_happened = false;
						}
					});
			});
}