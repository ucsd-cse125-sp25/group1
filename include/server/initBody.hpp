#pragma once

#include <glm/glm.hpp>
#include "components/frog.hpp"
#include "components/door.hpp"
#include "components/lilyPad.hpp"
#include "components/object.hpp"
#include "components/room.hpp"
#include "components/water.hpp"
#include "rigidBody.hpp"
#include "swamp.hpp"

class Swamp;

struct TransformData {
    glm::vec3 roomPosition;
    glm::vec3 position;
    glm::vec3 relativePosition;
    glm::vec3 relativeMinCorner;
    glm::vec3 relativeMaxCorner;
};

RigidBody* initObject(TransformData data);

RigidBody* initDoor(TransformData data);

RigidBody* initFrog(TransformData data);

RigidBody* initLilyPad(TransformData data, Swamp* swamp);

RigidBody* initWater(TransformData data, Swamp* swamp);
