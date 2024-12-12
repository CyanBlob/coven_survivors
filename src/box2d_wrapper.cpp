#include "box2d_wrapper.h"
#include "box2d/math_functions.h"
#include "box2d/box2d.h"
#include "components.h"
#include "entt/entity/registry.hpp"

b2WorldId Box2dWrapper::worldId = {};

void Box2dWrapper::init() {
    float lengthUnitsPerMeter = 64.0f;
    b2SetLengthUnitsPerMeter(lengthUnitsPerMeter);

    b2WorldDef worldDef = b2DefaultWorldDef();

    // Realistic gravity is achieved by multiplying gravity by the length unit.
    //worldDef.gravity.y = .1f * lengthUnitsPerMeter;
    worldDef.gravity.y = 0;
    worldId = b2CreateWorld(&worldDef);
}


void Box2dWrapper::debug_draw_colliders(entt::registry &registry) {
    auto view = registry.view<Box2D>();
    for (auto [entity, b2d]: view.each()) {
        auto body = b2Body_GetTransform(b2d.body);
        b2Vec2 p = b2Body_GetPosition(b2d.body);

        b2ShapeId shape;
        b2Body_GetShapes(b2d.body, &shape, 1);

        auto circle = b2Shape_GetCircle(shape);

        DrawCircle(p.x + circle.center.x, p.y + circle.center.y, circle.radius, BLUE);

        //auto polygon = b2Shape_GetPolygon(shape);
        /*for (int i = 0; i < 8; ++i) {
            b2Vec2 firstPoint = polygon.vertices[i];
            b2Vec2 nextPoint = polygon.vertices[(i + 1) % 8];

            DrawLine(firstPoint.x + p.x + 8, firstPoint.y + p.y + 8, nextPoint.x + p.x + 8, nextPoint.y + p.y + 8, BLUE);
            DrawCircle(p.x + 8, p.y + 8, polygon.radius, BLUE);
        }*/
    }
}
