#include "box2d_wrapper.h"
#include "box2d/math_functions.h"
#include "box2d/box2d.h"

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
