#include "initBody.hpp"

RigidBody* initObject(TransformData data, std::unordered_map<int, Object*>* objects) {
    Object* object = new Object(objects->size());
    (*objects)[object->getID()] = object;

    // Default object creation
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, object, true);

    object->setBody(body);
    return body;
}

RigidBody* initDoor(TransformData data, std::unordered_map<int, Door*>* doors) {
    int roomID1 = 0;
    int roomID2 = 0;
    int keyID = 0;
    Door* door = new Door(doors->size(), roomID1, roomID2, keyID);
    (*doors)[door->getID()] = door;

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, door, true);

    door->setBody(body);
    return body;
}

RigidBody* initFrog(TransformData data, std::unordered_map<int, Object*>* objects, Swamp* swamp) {
    auto frog = std::make_unique<Frog>(objects->size(), swamp);

    Frog* frogPtr = frog.get();
    (*objects)[frog->getID()] = frog.get();

    swamp->addInteractable(std::move(frog));

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, frogPtr, true);

    frogPtr->setBody(body);
    return body;
}

RigidBody* initLilyPad(TransformData data, Swamp* swamp) {
    auto [lilyPad, colliderType] = swamp->createLilyPad();

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{colliderType, data.relativeMinCorner, data.relativeMaxCorner}, lilyPad,
        true);

    lilyPad->setBody(body);
    return body;
}

RigidBody* initWater(TransformData data, Swamp* swamp) {
    Water* waterRespawnPlane = swamp->createWaterRespawn();

    // TODO: add the position/relative position in the json dimensions file
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{NONE, data.relativeMinCorner, data.relativeMaxCorner}, waterRespawnPlane,
        true);

    waterRespawnPlane->setBody(body);
    return body;
}

RigidBody* initCannonball(TransformData data, Circus* circus) {
    glm::vec3 absolutePosition = data.roomPosition + data.position + data.relativePosition;
    // TODO: is this bad? createCannonball expects cannon position, but we give cannonball position
    Cannonball* cannonball = circus->createCannonball(absolutePosition);

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f, new Transform{absolutePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, cannonball, true);

    cannonball->setBody(body);
    return body;
}

RigidBody* initWall(TransformData data, Circus* circus) {
    Object* wall = circus->createWall();

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, wall, true);

    wall->setBody(body);
    return body;
}
