#include "ecsScript.h"
#include "ecsSystems.h"
#include "../ScriptSystem/ScriptSystem.h"

void register_ecs_script_systems(flecs::world& ecs)
{
    static auto scriptQuery = ecs.query<ScriptSystemPtr>();
    ecs.system<const ScriptProxy>()
        .each([&](flecs::entity e, const ScriptProxy& scriptProxy)
            {
                scriptQuery.each([&](ScriptSystemPtr ss)
                    {
                        auto* sp = ss.ptr->CreateProxy(scriptProxy.script_file.data());

                        e.set(ScriptProxyPtr{ sp });
                        e.remove<ScriptProxy>();
                    });
            });
}
