#include <Windows.h>
#include "flecs.h"

#include "RenderProxy.h"
#include "ecsTimers.h"
#include "ecsGun.h"
#include "ecsMesh.h"

void register_ecs_timer_systems(flecs::world& ecs)
{
	ecs.system<Gun, ReloadTimer>()
		.each([&](flecs::entity e, Gun& gun, ReloadTimer& timer)
			{
				timer.elapsed += e.delta_time();

				if (timer.elapsed >= timer.reloadTime)
				{
					gun.numRounds = gun.capacity;
					e.remove<ReloadTimer>();
				}
			});

	ecs.system<SelfDestroyTimer, RenderProxyPtr>()
		.each([&](flecs::entity e, SelfDestroyTimer& timer, RenderProxyPtr& ptr)
			{
				timer.elapsed += e.delta_time();

				if (timer.elapsed >= timer.time)
				{
					ptr.ptr->SetRendered(false);
					e.destruct();
				}
			});
}