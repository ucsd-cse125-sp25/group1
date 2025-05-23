#include "initBody.hpp"

RigidBody* initObject(TransformData data, Server* serverRef) {
    Object object = new Object(serverRef->objects.size());

    // Default object creation
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, object, true);

    object->setBody(body);
    return body;
}

RigidBody* initDoor(TransformData data, Server* serverRef) {
    int roomID1 = 0;
    int roomID2 = 0;
    int keyID;
    Door door = new Door(serverRef->doors.size(), roomID1, roomID2, keyID);

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, door, true);

    door->setBody(body);
    return body;
}

RigidBody* initFrog(TransformData data, Server* serverRef) {
    Frog frog = new Frog(serverRef->objects.size());

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, frog, true);

    frog->setBody(body);
    return body;
}

RigidBody* initLilyPad(TransformData data, Server* serverRef) {
    auto [lilyPad, colliderType] = serverRef->swamp->createLilyPad();

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{colliderType, data.relativeMinCorner, data.relativeMaxCorner}, lilyPad,
        true);

    lilyPad->setBody(body);
    return body;
}

RigidBody* initWater(TransformData data, Server* serverRef) {
    Water* waterRespawnPlane = serverRef->swamp->createWaterRespawn();

    // TODO: add the position/relative position in the json dimensions file
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{NONE, data.relativeMinCorner, data.relativeMaxCorner}, waterRespawnPlane,
        true);

    waterRespawnPlane->setBody(body);
    return body;
}
