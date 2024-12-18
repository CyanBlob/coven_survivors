#ifndef COVEN_SURVIVORS_RENDERER_H
#define COVEN_SURVIVORS_RENDERER_H

#include "raylib.h"

class renderer {
public:
    static void begin(const Camera2D &camera);
    static void end();
    static void renderSprites();
    static void renderCollisionText(bool collision);
    static void renderUI();
    static void init();

    static const int screenWidth = 1920;
    static const int screenHeight = 1080;
    static const int screenUpperLimit = 40;      // Top menu limits


};


#endif //COVEN_SURVIVORS_RENDERER_H
