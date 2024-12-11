#ifndef COVEN_SURVIVORS_COMPONENTS_H
#define COVEN_SURVIVORS_COMPONENTS_H

#include "raylib.h"

struct Position {
    Vector2 pos;
};

struct Velocity {
    Vector2 vel;
};

struct Sprite {
    int height;
    int width;
    Color color;
};

#endif //COVEN_SURVIVORS_COMPONENTS_H
