#include <Windows.h>

#include "flecs.h"

#include "ecsTimers.h"
#include "ecsGun.h"

void register_ecs_timer_systems(flecs::world& ecs)
{
	ecs.system<Gun, ReloadTimer>()
		.each([&](flecs::entity e, Gun& gun, ReloadTimer& timer)
			{
				wchar_t str[128];
				swprintf_s(str, L"Updating reload timer, elapsed before update: %f\n", timer.elapsed);
				OutputDebugString(str);
				timer.elapsed += e.delta_time();

				if (timer.elapsed >= timer.reloadTime)
				{
					gun.numRounds = gun.capacity;
					e.remove<ReloadTimer>();
				}
			});
}