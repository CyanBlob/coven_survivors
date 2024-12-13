#ifndef COVEN_SURVIVORS_COMPONENTS_H
#define COVEN_SURVIVORS_COMPONENTS_H

#include "raylib.h"
#include "box2d/box2d.h"

struct Position {
    Vector2 pos;
};

struct Velocity {
    Vector2 vel;
};

struct Speed {
    float speed;
};

struct ShootPlayer {
    float speed;
    float rate;
    float cd;
    int damage;
};

struct Bullet {
    int damage;
};

struct Lifetime {
    float time;
    b2BodyId body;
};

struct Sprite {
    int height;
    int width;
    Color color;
};

struct Box2D {
    b2BodyId body;
};

struct ChasePlayer {
    bool chase;
};

#endif //COVEN_SURVIVORS_COMPONENTS_H
