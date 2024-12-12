#ifndef COVEN_SURVIVORS_BOX2D_WRAPPER_H
#define COVEN_SURVIVORS_BOX2D_WRAPPER_H


#include "box2d/id.h"

class Box2dWrapper {
public:
    static void init();

    static b2WorldId worldId;
};


#endif //COVEN_SURVIVORS_BOX2D_WRAPPER_H
