#include "renderer.h"
#include "components.h"
#include "entt/entt.hpp"
#include "entt_helpers.h"
#include <iostream>

#include "raylib.h"

void renderer::begin() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void renderer::end() {
    EndDrawing();
}

void renderer::renderSprites() {
    // Use EnTT to draw entities
    auto spritesView = entt_helpers::registry.view<const Sprite, const Box2D>();

    spritesView.each([](const Sprite &sprite, const auto &b2d) {
        b2Vec2 p = b2Body_GetPosition(b2d.body);
        DrawRectangle((int)p.x, (int)p.y, sprite.width, sprite.height, sprite.color);
    });
}

void renderer::renderCollisionText(bool collision) {
    if (collision)
    {
        // Draw collision area
        //DrawRectangleRec(boxCollision, LIME);

        // Draw collision message
        //DrawText("COLLISION!", GetScreenWidth()/2 - MeasureText("COLLISION!", 20)/2, screenUpperLimit/2 - 10, 20, BLACK);

        // Draw collision area
        //DrawText(TextFormat("Collision Area: %i", (int)boxCollision.width*(int)boxCollision.height), GetScreenWidth()/2 - 100, screenUpperLimit + 10, 20, BLACK);
    }

}

void renderer::renderUI() {
    // Draw help instructions
    DrawText("Press SPACE to PAUSE/RESUME", 20, screenHeight - 35, 20, LIGHTGRAY);

    DrawFPS(10, 10);
}

void renderer::init() {
    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - collision area");
}
