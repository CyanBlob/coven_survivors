#ifndef COVEN_SURVIVORS_BOX2D_WRAPPER_H
#define COVEN_SURVIVORS_BOX2D_WRAPPER_H


#include "box2d/id.h"
#include "entt/entity/registry.hpp"

//#include "box2cpp/box2cpp.h"

class Box2dWrapper {
public:
    static void init();

    static void debug_draw_colliders(entt::registry &registry);

    static b2WorldId worldId;

};


#endif //COVEN_SURVIVORS_BOX2D_WRAPPER_H
