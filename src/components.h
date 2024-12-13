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

struct Sprite {
    int height;
    int width;
    Color color;
};

struct Box2D {
    b2BodyId body;
};

#endif //COVEN_SURVIVORS_COMPONENTS_H
