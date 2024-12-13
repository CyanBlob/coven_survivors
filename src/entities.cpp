#include "entities.h"
#include "box2d_wrapper.h"
#include "raymath.h"
#include "renderer.h"
#include "player.h"

b2BodyId Entities::playerId = b2BodyId();

void Entities::physics_update(entt::registry &registry) {
    b2World_Step(Box2dWrapper::worldId, GetFrameTime(), 4);
    auto view = registry.view<Speed, Box2D>();

    for (auto [entity, speed, b2d]: view.each()) {

        auto target = b2Normalize(b2Body_GetPosition(playerId) - b2Body_GetPosition(b2d.body));
        target *= GetFrameTime() * speed.speed;
        //auto scaledVel = Vector2Scale(vel.vel, GetFrameTime());

        //b2Body_ApplyForceToCenter(b2d.body, b2Vec2{scaledVel.x, scaledVel.y}, false);
        b2Body_SetLinearVelocity(b2d.body, b2Vec2{target.x, target.y});
    }
}

void Entities::update(entt::registry &registry) {
    //b2World_Step(Box2dWrapper::worldId, GetFrameTime(), 4);
    auto view = registry.view<Speed, Box2D>();

    // use a callback
    //view.each([](const auto &pos, auto &vel) {
    //});

    // use an extended callback
    //view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    auto i = 0;
    // use a range-for
    for (auto [entity, vel, b2d]: view.each()) {

        //b2Vec2 p = b2Body_GetPosition(b2d.body);

        //std::cout << ++i << ": " << p.x << ", " << p.y << std::endl;
    }

    // use forward iterators and get only the components of interest
    /*for (auto entity: view) {
        auto &vel = view.get<Velocity>(entity);
        // ...
    }*/
}

b2BodyId Entities::spawn() {
    const auto entity = entt_helpers::registry.create();

    entt_helpers::registry.emplace<Sprite>(entity, 16, 16, PINK);
    entt_helpers::registry.emplace<Speed>(entity, 5000.f);
    //entt_helpers::registry.emplace<Velocity>(entity,
    //static_cast<float>(GetRandomValue(-1000, 1000)),
    //static_cast<float>(GetRandomValue(-1000, 1000)));

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
