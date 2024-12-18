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

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"


#include <iostream>
#include <sstream>

#include "entt/entt.hpp"
#include "components.h"
#include "entities.h"
#include "renderer.h"
#include "entt_helpers.h"

#include "box2d_wrapper.h"
#include "player.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //---------------------------------------------------------
    renderer::init();
    Box2dWrapper::init();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    bool pause = false;
    bool debug = false;

    SetRandomSeed(0);

    Player player;

    Entities::playerId = player.bodyId;

    //EnTT------------------------------------------------------
    TraceLog(LOG_INFO, "Spawning initial entities\n");

    double startTime = GetTime();

    for (auto i = 0u; i < 1000u; ++i) {
        Entities::spawn();
    }
    TraceLog(LOG_INFO, "Done spawning initial entities (took %fms)\n", (GetTime() - startTime) * 1000);
    //----------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;
        }
        if (IsKeyPressed(KEY_GRAVE)) {
            debug = !debug;
        }

        if (!pause) {
            player.physics_update(entt_helpers::registry);
            player.update(entt_helpers::registry);
        }

        // Flush input event buffer?
        PollInputEvents();

        if (!pause) {
            if (debug) {
                startTime = GetTime();
            }
            Entities::physics_update(entt_helpers::registry);
            if (debug) {
                TraceLog(LOG_INFO, "Entity physics took %fms", (GetTime() - startTime) * 1000);
                startTime = GetTime();
            }
            Entities::update(entt_helpers::registry);
            if (debug) {
                TraceLog(LOG_INFO, "Entity update took %fms", (GetTime() - startTime) * 1000);
            }
        }

        // Draw
        //-----------------------------------------------------
        renderer::begin(player.get_camera());

        if (debug) {
            startTime = GetTime();
        }
        renderer::renderSprites();

        if (debug) {
            TraceLog(LOG_INFO, "Render sprites took %fms", (GetTime() - startTime) * 1000);
        }

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

        if (debug) {
            EndMode2D(); // ignore camera; draw to screen

            DrawFPS(0, 0);
            auto view = entt_helpers::registry.view<entt::entity>();
            std::size_t count = entt_helpers::registry.storage<entt::entity>().size();

            std::stringstream ss;
            ss << "Entities: " << count;
            DrawText(ss.str().c_str(), 0, 16, 20, DARKGREEN);
            DrawCircle(renderer::screenWidth / 2, renderer::screenHeight / 2, 4, PURPLE);

            BeginMode2D(player.get_camera()); // resume drawing to camera
            //Box2dWrapper::debug_draw_colliders(entt_helpers::registry);
        }


        renderer::end();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}