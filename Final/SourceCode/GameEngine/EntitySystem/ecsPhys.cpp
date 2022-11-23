#include "ecsPhys.h"
#include "ecsGun.h"
#include "ecsMesh.h"
#include "RenderProxy.h"

#include "ecsTimers.h"
#include <cstdlib>
#include <cmath>

static float rand_flt(float from, float to)
{
    return from + (float(rand()) / RAND_MAX) * (to - from);
}

static bool box_intersection(const Position& pos, const BoundingBox& bbox, const Position& rhsPos, const BoundingBox& rhsBbox)
{
    return (std::abs(pos.x - rhsPos.x) < (bbox.x + rhsBbox.x))
        && (std::abs(pos.y - rhsPos.y) < (bbox.y + rhsBbox.y))
        && (std::abs(pos.z - rhsPos.z) < (bbox.z + rhsBbox.z));
}

void register_ecs_phys_systems(flecs::world& ecs)
{
    ecs.system<Velocity, const Gravity, BouncePlane*, Position*>()
        .each([&](flecs::entity e, Velocity& vel, const Gravity& grav, BouncePlane* plane, Position* pos)
            {
                if (plane && pos)
                {
                    constexpr float planeEpsilon = 0.1f;
                    if (plane->x * pos->x + plane->y * pos->y + plane->z * pos->z < plane->w + planeEpsilon)
                        return;
                }
                vel.x += grav.x * e.delta_time();
                vel.y += grav.y * e.delta_time();
                vel.z += grav.z * e.delta_time();
            });

    ecs.system<const Bullet, const Position, DeathPlane*>()
        .each([&](flecs::entity e, const Bullet&, const Position& pos, DeathPlane* plane)
            {
                if (plane)
                {
                    constexpr float planeEpsilon = 0.1f;
                    if (plane->x * pos.x + plane->y * pos.y + plane->z * pos.z < plane->w + planeEpsilon)
                    {
                        if (!e.has<SelfDestroyTimer>())
                        {
                            e.set(SelfDestroyTimer{ 5, 0 });
                        }
                    }
                }
            });

    static auto targetQuery = ecs.query<const Target, const Position, const BoundingBox, RenderProxyPtr>();
    static auto gunQuery = ecs.query<Gun>();
    ecs.system<const Position, Bullet, const BoundingBox, RenderProxyPtr>()
        .each([&](flecs::entity e, const Position& pos, Bullet&, const BoundingBox& bbox, RenderProxyPtr& ptr)
            {
                targetQuery.each([&](flecs::entity t, const Target& target, const Position& targetPos, const BoundingBox& targetBbox, RenderProxyPtr& targetPtr)
                    {
                        if (box_intersection(pos, bbox, targetPos, targetBbox))
                        {
                            gunQuery.each([&](Gun& gun) { gun.numRounds += min(target.bonus, gun.capacity - gun.numRounds); });
                            targetPtr.ptr->SetRendered(false);
                            t.mut(e).destruct();
                        }
                    });
            });


    ecs.system<Velocity, Position, const BouncePlane, const Bounciness>()
        .each([&](Velocity& vel, Position& pos, const BouncePlane& plane, const Bounciness& bounciness)
            {
                float dotPos = plane.x * pos.x + plane.y * pos.y + plane.z * pos.z;
                float dotVel = plane.x * vel.x + plane.y * vel.y + plane.z * vel.z;
                if (dotPos < plane.w)
                {
                    pos.x -= (dotPos - plane.w) * plane.x;
                    pos.y -= (dotPos - plane.w) * plane.y;
                    pos.z -= (dotPos - plane.w) * plane.z;

                    vel.x -= (1.f + bounciness.val) * plane.x * dotVel;
                    vel.y -= (1.f + bounciness.val) * plane.y * dotVel;
                    vel.z -= (1.f + bounciness.val) * plane.z * dotVel;
                }
            });


    ecs.system<Velocity, const FrictionAmount>()
        .each([&](flecs::entity e, Velocity& vel, const FrictionAmount& friction)
            {
                vel.x -= vel.x * friction.val * e.delta_time();
                vel.y -= vel.y * friction.val * e.delta_time();
                vel.z -= vel.z * friction.val * e.delta_time();
            });


    ecs.system<Position, const Velocity>()
        .each([&](flecs::entity e, Position& pos, const Velocity& vel)
            {
                pos.x += vel.x * e.delta_time();
                pos.y += vel.y * e.delta_time();
                pos.z += vel.z * e.delta_time();
            });


    ecs.system<Position, const ShiverAmount>()
        .each([&](flecs::entity e, Position& pos, const ShiverAmount& shiver)
            {
                pos.x += rand_flt(-shiver.val, shiver.val);
                pos.y += rand_flt(-shiver.val, shiver.val);
                pos.z += rand_flt(-shiver.val, shiver.val);
            });
}

