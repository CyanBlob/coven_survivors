#ifndef COVEN_SURVIVORS_PLAYER_H
#define COVEN_SURVIVORS_PLAYER_H

#include "entt/entity/entity.hpp"
#include "box2d/box2d.h"
#include "raylib.h"
#include "raymath.h"

class Player {
public:
    Player();

    void physics_update(entt::registry &registry);

    void update(entt::registry &registry);
    b2Vec2 getPosition();

    const Camera2D& get_camera() {return camera;}

    entt::entity entity;
    b2BodyId bodyId{};

private:
    Vector2 baseVel = {8000.f, 8000.f};
    Camera2D camera{0};
};


#endif //COVEN_SURVIVORS_PLAYER_H
