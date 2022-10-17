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
											.set(Velocity{ vel.x, vel.y, vel.z + gun.muzzleSpeed })
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
								e.set(ReloadTimer{ gun.reloadTime, 0 });
							}
						}
						else
						{
							shot_happened = false;
						}
					});
			});
}