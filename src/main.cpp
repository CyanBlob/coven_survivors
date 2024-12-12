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
#include <sstream>

#include "entt/entt.hpp"
#include "components.h"
#include "renderer.h"
#include "entt_helpers.h"

#include "box2d/math_functions.h"
#include "box2d/box2d.h"
#include "box2d_wrapper.h"

//#include "box2cpp/box2cpp.h"

void debug_draw_colliders(entt::registry &registry) {
    auto view = registry.view<Velocity, Box2D>();
    for (auto [entity, vel, b2d]: view.each()) {
        auto body = b2Body_GetTransform(b2d.body);
        b2Vec2 p = b2Body_GetPosition(b2d.body);

        b2ShapeId shape;
        b2Body_GetShapes(b2d.body, &shape, 1);

        auto circle = b2Shape_GetCircle(shape);

        DrawCircle(p.x + 8, p.y + 8, circle.radius, BLUE);

        //auto polygon = b2Shape_GetPolygon(shape);
        /*for (int i = 0; i < 8; ++i) {
            b2Vec2 firstPoint = polygon.vertices[i];
            b2Vec2 nextPoint = polygon.vertices[(i + 1) % 8];

            DrawLine(firstPoint.x + p.x + 8, firstPoint.y + p.y + 8, nextPoint.x + p.x + 8, nextPoint.y + p.y + 8, BLUE);
            DrawCircle(p.x + 8, p.y + 8, polygon.radius, BLUE);
        }*/
    }
}

void physics_update(entt::registry &registry) {
    b2World_Step(Box2dWrapper::worldId, GetFrameTime(), 4);
    auto view = registry.view<Velocity, Box2D>();

    for (auto [entity, vel, b2d]: view.each()) {

        auto scaledVel = Vector2Scale(vel.vel, GetFrameTime());

        //b2Body_ApplyForceToCenter(b2d.body, b2Vec2{scaledVel.x, scaledVel.y}, false);
        b2Body_SetLinearVelocity(b2d.body, b2Vec2{scaledVel.x, scaledVel.y});
    }
}

void update(entt::registry &registry) {
    //b2World_Step(Box2dWrapper::worldId, GetFrameTime(), 4);
    auto view = registry.view<Velocity, Box2D>();

    // use a callback
    //view.each([](const auto &pos, auto &vel) {
    //});

    // use an extended callback
    //view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    auto i = 0;
    // use a range-for
    for (auto [entity, vel, b2d]: view.each()) {

        //b2Vec2 p = b2Body_GetPosition(b2d.body);

        //std::cout << ++i << ": " << p.x << ", " << p.y << std::endl;
    }

    // use forward iterators and get only the components of interest
    /*for (auto entity: view) {
        auto &vel = view.get<Velocity>(entity);
        // ...
    }*/
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //---------------------------------------------------------
    renderer::init();
    Box2dWrapper::init();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    bool pause = false;
    bool debug = false;

    //EnTT------------------------------------------------------
    for (auto i = 0u; i < 10u; ++i) {
        const auto entity = entt_helpers::registry.create();
        const auto x = (float) i;
        entt_helpers::registry.emplace<Sprite>(entity, 16, 16, PINK);
        entt_helpers::registry.emplace<Velocity>(entity, (10 - x) * 100.f, (10 - x) * 10.f);

        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = (b2Vec2) {x * 16, 16};


        auto bodyId = b2CreateBody(Box2dWrapper::worldId, &bodyDef);

        b2ShapeDef shapeDef = b2DefaultShapeDef();

        //shapeDef.density = 1.0f; // Set density
        b2Circle circle = {0, 0, 8.0f}; // Center at (0,0) with radius 1
        b2ShapeId shapeId = b2CreateCircleShape(bodyId, &shapeDef, &circle);

        //b2Polygon boxPolygon = b2MakeRoundedBox(4, 8, 2);
        //b2CreatePolygonShape(bodyId, &shapeDef, &boxPolygon);

        entt_helpers::registry.emplace<Box2D>(entity, bodyId);
    }
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
            physics_update(entt_helpers::registry);
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

        if (debug) {
            DrawFPS(0, 0);
            auto view = entt_helpers::registry.view<entt::entity>();
            std::size_t count = entt_helpers::registry.storage<entt::entity>().size();

            std::stringstream ss;
            ss << "Entities: " << count;
            DrawText(ss.str().c_str(), 0, 16, 20, DARKGREEN);
            debug_draw_colliders(entt_helpers::registry);
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