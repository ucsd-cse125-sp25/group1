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

RigidBody* initFrog(TransformData data, std::unordered_map<int, Object*>* objects) {
    Frog* frog = new Frog(objects->size());
    (*objects)[frog->getID()] = frog;

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, frog, true);

    frog->setBody(body);
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

RigidBody* initKey(TransformData data, Server& server, World& world, const std::string& roomName){//Switch this to ID) 
    Key* key = new Key(0, roomName, server, world);

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, key, true);

    key->setBody(body);
    return body;
}

