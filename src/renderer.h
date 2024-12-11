#ifndef COVEN_SURVIVORS_RENDERER_H
#define COVEN_SURVIVORS_RENDERER_H


class renderer {
public:
    static void begin();
    static void end();
    static void renderSprites();
    static void renderCollisionText(bool collision);
    static void renderUI();
    static void init();

    static const int screenWidth = 800;
    static const int screenHeight = 450;
    static const int screenUpperLimit = 40;      // Top menu limits


};


#endif //COVEN_SURVIVORS_RENDERER_H
