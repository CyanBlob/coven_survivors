#include "player.h"
#include "entt_helpers.h"
#include "components.h"
#include "box2d_wrapper.h"
#include "renderer.h"

Player::Player() {
    entity = entt_helpers::registry.create();
    entt_helpers::registry.emplace<Sprite>(entity, 32, 32, ORANGE);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2) {renderer::screenWidth / 2.f, renderer::screenHeight / 2.f};


    bodyId = b2CreateBody(Box2dWrapper::worldId, &bodyDef);

    b2ShapeDef shapeDef = b2DefaultShapeDef();

    shapeDef.density = 100.0f; // Set density
    b2Circle circle = {0, 0, 16.0f};
    b2CreateCircleShape(bodyId, &shapeDef, &circle);

    entt_helpers::registry.emplace<Box2D>(entity, bodyId);

    camera.target = (Vector2){0.0f, 0.0f};     // The point the camera follows
    camera.offset = (Vector2){renderer::screenWidth / 2.f, renderer::screenHeight / 2.f};
    camera.rotation = 0.0f;                    // No rotation initially
    camera.zoom = 1.0f;                        // Default zoom
}

void Player::physics_update(entt::registry &registry) {
    auto scaledVel = Vector2Scale(baseVel, GetFrameTime());
    Vector2 movementVec = {0, 0};

    if (IsKeyDown(KEY_W)) {
        movementVec.y -= scaledVel.y;
    }
    if (IsKeyDown(KEY_S)) {
        movementVec.y += scaledVel.y;
    }
    if (IsKeyDown(KEY_A)) {
        movementVec.x -= scaledVel.x;
    }
    if (IsKeyDown(KEY_D)) {
        movementVec.x += scaledVel.x;
    }

    //b2Body_ApplyForceToCenter(b2d.body, b2Vec2{scaledVel.x, scaledVel.y}, false);
    b2Body_SetLinearVelocity(bodyId, b2Vec2{movementVec.x, movementVec.y});

}

void Player::update(entt::registry &registry) {
    auto pos = b2Body_GetPosition(bodyId);
    camera.target = (Vector2) {pos.x, pos.y};
}

b2Vec2 Player::getPosition() {
    return b2Body_GetPosition(bodyId);
}
