#include "initBody.hpp"

RigidBody* initObject(TransformData data) {
    // Default object creation
    object = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data->roomPosition + data->position + data->relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data->relativeMinCorner, data->relativeMaxCorner}, nullptr, true);

    return object;
}

RigidBody* initDoor(TransformData data) {
    return nullptr;
}

RigidBody* initFrog(TransformData data) {
    return nullptr;
}

RigidBody* initLilyPad(TransformData data, Swamp* swamp) {
    auto [lilyPad, colliderType] = swamp->createLilyPad();

    object = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data->roomPosition + data->position + data->relativePosition, vec3(0.0f)},
        new BoxCollider{colliderType, data->relativeMinCorner, data->relativeMaxCorner}, lilyPad,
        true);

    lilyPad->setBody(object);
    return object;
}

RigidBody* initWater(TransformData data, Swamp* swamp) {
    Water* waterRespawnPlane = swamp->createWaterRespawn();

    // TODO: add the position/relative position in the json dimensions file
    object = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data->roomPosition + data->position + data->relativePosition, vec3(0.0f)},
        new BoxCollider{NONE, data->relativeMinCorner, data->relativeMaxCorner}, waterRespawnPlane,
        true);

    waterRespawnPlane->setBody(object);
    return object;
}
