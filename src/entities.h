#ifndef COVEN_SURVIVORS_ENTITIES_H
#define COVEN_SURVIVORS_ENTITIES_H

#include "entt_helpers.h"
#include "components.h"
#include "box2d/box2d.h"

class Entities {
public:
    static b2BodyId spawn();
    static void physics_update(entt::registry &registry);
    static void update(entt::registry &registry);

};


#endif //COVEN_SURVIVORS_ENTITIES_H
