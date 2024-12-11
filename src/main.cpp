/*******************************************************************************************
*
*   raylib [shapes] example - collision area
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

#include <cstdlib>
#include <iostream>

#include "entt/entt.hpp"
#include "components.h"
#include "renderer.h"
#include "entt_helpers.h"


void update(entt::registry &registry) {
    auto view = registry.view<Position, Velocity>();

    // use a callback
    view.each([](const auto &pos, auto &vel) {
    });

    // use an extended callback
    view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    // use a range-for
    for (auto [entity, pos, vel]: view.each()) {

        auto scaledVel = Vector2Scale(vel.vel, GetFrameTime());
        pos.pos.x += scaledVel.x;
        pos.pos.y += scaledVel.y;
    }

    // use forward iterators and get only the components of interest
    for (auto entity: view) {
        auto &vel = view.get<Velocity>(entity);
        // ...
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //---------------------------------------------------------
    renderer::init();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    bool pause = false;             // Movement pause

    //EnTT------------------------------------------------------
    for (auto i = 0u; i < 10u; ++i) {
        const auto entity = entt_helpers::registry.create();
        const auto x = (float)i;
        entt_helpers::registry.emplace<Position>(entity, x * 1.f, x * 1.f);
        entt_helpers::registry.emplace<Sprite>(entity, 16, 16, PINK);
        entt_helpers::registry.emplace<Velocity>(entity, x * 3.1f, x * 3.1f);
    }
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;
        }

        if (!pause) {
            update(entt_helpers::registry);
        }

        // Draw
        //-----------------------------------------------------
        renderer::begin();
        renderer::renderSprites();

        if (pause) {
            float popupWidth = 250;
            float popupHeight = 100;
            int result = GuiMessageBox((Rectangle) {
                                               static_cast<float>(renderer::screenWidth / 2.0 - popupWidth / 2),
                                               static_cast<float>(renderer::screenHeight / 2.0 - popupHeight / 2),
                                               popupWidth, popupHeight},
                                       "#191#Game Paused", "Game Paused. Press \"space\" to resume", "Nice;Resume");
            if (result == 2) {
                pause = false;
            }
        }

        // Flush input event buffer?
        PollInputEvents();
        renderer::end();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}