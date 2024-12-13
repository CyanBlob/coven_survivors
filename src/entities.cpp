#include "entities.h"
#include "box2d_wrapper.h"
#include "raymath.h"
#include "renderer.h"
#include "player.h"

b2BodyId Entities::playerId = b2BodyId();

void Entities::physics_update(entt::registry &registry) {
    b2World_Step(Box2dWrapper::worldId, GetFrameTime(), 4);

    // Destroy temporary entities
    auto lifetimeDespawnView = registry.view<Lifetime>();
    for (auto [entity, lifetime]: lifetimeDespawnView.each()) {
        lifetime.time -= GetFrameTime();

        if (lifetime.time <= 0) {
            b2DestroyBody(lifetime.body);
            entt_helpers::registry.destroy(entity);
        }
    }

    // Have enemies follow player
    auto view = registry.view<Speed, Box2D, ChasePlayer>();
    for (auto [entity, speed, b2d, ChasePlayer]: view.each()) {

        auto target = b2Normalize(b2Body_GetPosition(playerId) - b2Body_GetPosition(b2d.body));
        target *= GetFrameTime() * speed.speed;

        b2Body_SetLinearVelocity(b2d.body, b2Vec2{target.x, target.y});
    }

    // Shoot bullets
    auto shootPlayerView = registry.view<ShootPlayer, Box2D>();
    for (auto [entity, shot, b2d]: shootPlayerView.each()) {

        shot.cd -= GetFrameTime();

        if (shot.cd <= 0) {
            shot.cd = shot.rate;

            const auto bulletEntity = entt_helpers::registry.create();

            entt_helpers::registry.emplace<Sprite>(bulletEntity, 8, 8, BLUE);

            auto target = b2Normalize(b2Body_GetPosition(playerId) - b2Body_GetPosition(b2d.body));
            target *= GetFrameTime() * shot.speed;

            b2BodyDef bodyDef = b2DefaultBodyDef();
            bodyDef.type = b2_kinematicBody;

            bodyDef.position = b2Body_GetPosition(b2d.body);

            auto bulletBodyId = b2CreateBody(Box2dWrapper::worldId, &bodyDef);

            b2ShapeDef shapeDef = b2DefaultShapeDef();

            shapeDef.isSensor = true;
            b2Circle circle = {0, 0, 4.0f}; // Center at (0,0) with radius 1
            b2CreateCircleShape(bulletBodyId, &shapeDef, &circle);

            entt_helpers::registry.emplace<Box2D>(bulletEntity, bulletBodyId);

            b2Body_SetLinearVelocity(bulletBodyId, b2Vec2{target.x, target.y});


            entt_helpers::registry.emplace<Bullet>(bulletEntity, shot.damage);
            entt_helpers::registry.emplace<Lifetime>(bulletEntity, 4.f, bulletBodyId);
        }

    }
}

void Entities::update(entt::registry &registry) {
    auto view = registry.view<Speed, Box2D>();

    auto i = 0;
    // use a range-for
    for (auto [entity, vel, b2d]: view.each()) {

    }
}

b2BodyId Entities::spawn() {
    const auto entity = entt_helpers::registry.create();

    entt_helpers::registry.emplace<Sprite>(entity, 16, 16, PINK);
    entt_helpers::registry.emplace<Speed>(entity, 5000.f);
    entt_helpers::registry.emplace<ShootPlayer>(entity, 15000.f, 1.f, 1.f, 1);
    entt_helpers::registry.emplace<ChasePlayer>(entity, true);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;

    bodyDef.position = (b2Vec2) {static_cast<float>(GetRandomValue(0, renderer::screenWidth)),
                                 static_cast<float>(GetRandomValue(0, renderer::screenHeight))};


    auto bodyId = b2CreateBody(Box2dWrapper::worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();

    shapeDef.density = 1.0f; // Set density
    b2Circle circle = {0, 0, 8.0f}; // Center at (0,0) with radius 1
    b2ShapeId shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circle);

    //b2Polygon boxPolygon = b2MakeRoundedBox(4, 8, 2);
    //b2CreatePolygonShape(bodyId, &shapeDef, &boxPolygon);

    entt_helpers::registry.emplace<Box2D>(entity, bodyId);
    return bodyId;
}
