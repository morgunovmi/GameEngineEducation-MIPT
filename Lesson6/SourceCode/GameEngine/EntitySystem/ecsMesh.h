#pragma once
#include "flecs.h"

struct CubeMesh {};
struct OctaMesh {};
struct RenderProxyPtr
{
	class RenderProxy* ptr;
};

void register_ecs_mesh_systems(flecs::world& ecs);

