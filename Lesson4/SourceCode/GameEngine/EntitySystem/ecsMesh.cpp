#include "ecsMesh.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "RenderThread.h"
#include "RenderEngine.h"
#include "CubeRenderProxy.h"
#include "OctahedronRenderProxy.h"

void register_ecs_mesh_systems(flecs::world &ecs)
{
  static auto renderQuery = ecs.query<RenderEnginePtr>();
  ecs.system<const CubeMesh>()
    .each([&](flecs::entity e, const CubeMesh& cubeMesh)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
          RenderProxy* renderProxy = new OctahedronRenderProxy;
          re.ptr->GetRT()->EnqueueCommand(RC_CreateOctahedronRenderObject, renderProxy);

          float position[3];
          position[0] = 0.0f;
          position[1] = 0.0f;
          position[2] = 0.0f;

          renderProxy->SetPosition(position);
          renderProxy->SetScale(1.0f);

          e.set(RenderProxyPtr{ renderProxy });
          e.remove<CubeMesh>();
      });
    });

  ecs.system<RenderProxyPtr, const Position, const Scale>()
    .each([&](RenderProxyPtr &renderProxy, const Position &pos, const Scale &scale)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
           float position[3];
           position[0] = pos.x;
           position[1] = pos.y;
           position[2] = pos.z;

           renderProxy.ptr->SetPosition(position);
           renderProxy.ptr->SetScale(scale.s);
      });
    });
}

