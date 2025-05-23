#pragma once

#include "rigidBody.hpp"
#include "swamp.hpp"

struct TransformData {
    float roomPosition;
    float position;
    float relativePosition;
    float relativeMinCorner;
    float relativeMaxCorner;
};

RigidBody* initObject(TransformData data);

RigidBody* initDoor(TransformData data);

RigidBody* initFrog(TransformData data);

RigidBody* initLilyPad(TransformData data, Swamp* swamp);

RigidBody* initWater(TransformData data, Swamp* swamp);
