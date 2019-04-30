#include <include/ecs_rigid_body.h>

int main(int argc, char *argv[]) {
    /* Create the world, pass arguments for overriding the number of threads,fps
     * or for starting the admin dashboard (see flecs.h for details). */
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_IMPORT(world, FlecsComponentsTransform, 0);
    ECS_IMPORT(world, FlecsComponentsPhysics, 0);
    ECS_IMPORT(world, FlecsComponentsGeometry, 0);
    ECS_IMPORT(world, FlecsComponentsGraphics, 0);
    ECS_IMPORT(world, FlecsSystemsPhysics, 0);
    ECS_IMPORT(world, FlecsSystemsSdl2, 0);

    ECS_TYPE(world, Ball, EcsPosition2D, EcsVelocity2D, EcsCollider, EcsCircle, EcsRigidBody, EcsBounciness, EcsColor);

    ECS_ENTITY(world, LeftWall, EcsPosition2D, EcsCollider, EcsRectangle);
    ECS_ENTITY(world, BottomWall, EcsPosition2D, EcsCollider, EcsRectangle);
    ECS_ENTITY(world, RightWall, EcsPosition2D, EcsCollider, EcsRectangle);

    for (int i = 0; i < 100; i ++) {
        ecs_entity_t e = ecs_new(world, Ball);
        ecs_set(world, e, EcsPosition2D, {ecs_randf(36) - 18, ecs_randf(60) - 45});
        ecs_set(world, e, EcsVelocity2D, {ecs_randf(10) - 5, ecs_randf(10) - 5});
        ecs_set(world, e, EcsColor, {ecs_randf(255), ecs_randf(255), ecs_randf(255), 255});
        ecs_set(world, e, EcsBounciness, {0.7});
        ecs_set(world, e, EcsCircle, {0.5});
    }

    /* Initialize walls */
    ecs_set(world, LeftWall, EcsPosition2D, {-20, 15});
    ecs_set(world, LeftWall, EcsRectangle, {2, 32});
    ecs_set(world, LeftWall, EcsColor, {50, 50, 50, 255});

    ecs_set(world, RightWall, EcsPosition2D, {20, 15});
    ecs_set(world, RightWall, EcsRectangle, {2, 32});
    ecs_set(world, RightWall, EcsColor, {50, 50, 50, 255});

    ecs_set(world, BottomWall, EcsPosition2D, {0, 30});
    ecs_set(world, BottomWall, EcsRectangle, {38, 2});
    ecs_set(world, BottomWall, EcsColor, {50, 50, 50, 255});

    /* Create window */
    ecs_set_singleton(world, EcsCanvas2D, {
        .window = {800, 600},
        .viewport = {100, 75}
    });

    /* Set target FPS for main loop */
    ecs_set_target_fps(world, 120);

    /* Run systems */
    while ( ecs_progress(world, 0));

    /* Cleanup */
    return ecs_fini(world);
}
