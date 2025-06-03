#include "initBody.hpp"

RigidBody* initObject(TransformData data, std::unordered_map<int, Object*>* objects, World* world) {
    Object* object = new Object(objects->size());
    (*objects)[object->getID()] = object;

    // Default object creation
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, object, world, true);

    object->setBody(body);
    return body;
}

RigidBody* initDoor(TransformData data, std::unordered_map<int, Door*>* doors,
                    std::unordered_map<int, Room*>* rooms, World* world, Server& server) {
    int keyID = -1;
    int roomIDs[2] = {0, 4};

    Door* door;
    if (keyID != -1) {
        door = new Door(doors->size(), roomIDs[0], roomIDs[1], keyID, server);
    } else {
        door = new Door(doors->size(), roomIDs[0], roomIDs[1], server);
    }
    (*doors)[door->getID()] = door;

    (*rooms)[roomIDs[0]]->addInteractable(door);
    (*rooms)[roomIDs[1]]->addInteractable(door);

    vec3 doorPosition = data.roomPosition + data.position + data.relativePosition;
    vec3 facingDirection;
    vec3 relativeDifference = data.relativeMaxCorner - data.relativeMinCorner;
    if (relativeDifference.x < relativeDifference.z) {
        // Door's normal is parallel to the x-axis
        facingDirection = vec3(1.0f, 0.0f, 0.0f);
    } else {
        // Door's normal is parallel to the z-axis
        facingDirection = vec3(0.0f, 0.0f, 1.0f);
    }

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f, new Transform{doorPosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, door, world, true);

    RigidBody* roomZones[2];
    for (int i = -1; i < 2; i += 2) {
        // Shouldn't be a referenceable object
        Object* object = new Object(-1, [i, roomIDs](ICustomPhysics* otherObject) {
            // If the other object is a player, change their roomID
            if (Player* player = dynamic_cast<Player*>(otherObject)) {
                player->setCurRoomID(roomIDs[(i + 1) / 2]);
            }
        });

        // Create a rigid body that changes the roomID of players that collide with it
        float offset =
            i * config::PLAYER_WIDTH / 2; // first room is always most negative side of the door
        vec3 zonePosition = doorPosition + (offset * facingDirection);
        RigidBody* zone = new RigidBody(
            vec3(0.0f), vec3(0.0f), 0.0f, new Transform{zonePosition, vec3(0.0f)},
                          new BoxCollider{NONE, data.relativeMinCorner, data.relativeMaxCorner},
                          object, world, true);

        roomZones[(i + 1) / 2] = zone;
        world->addObject(zone);
    }

    door->setRoomZones(roomZones[0], roomZones[1]);
    door->setBody(body);

    return body;
}

RigidBody* initFrog(TransformData data, std::unordered_map<int, Object*>* objects, Swamp* swamp,
                    World* world) {
    Frog* frog = new Frog(objects->size(), swamp);

    swamp->addInteractable(frog);

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, frog, world, true);

    frog->setBody(body);
    return body;
}

RigidBody* initLilyPad(TransformData data, Swamp* swamp, World* world) {
    auto [lilyPad, colliderType] = swamp->createLilyPad();

    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{colliderType, data.relativeMinCorner, data.relativeMaxCorner}, lilyPad,
        world, true);

    lilyPad->setBody(body);
    return body;
}

RigidBody* initWater(TransformData data, Swamp* swamp, World* world) {
    Water* waterRespawnPlane = swamp->createWaterRespawn();

    // TODO: add the position/relative position in the json dimensions file
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{NONE, data.relativeMinCorner, data.relativeMaxCorner}, waterRespawnPlane,
        world, true);

    waterRespawnPlane->setBody(body);
    return body;
}

RigidBody* initKey(TransformData data, Server& server, World& world,
                   const std::string& roomName, std::unordered_map<int, Key*>* keys) { // Switch this to ID)
    // TODO: change this from 0 to whatever key ID
    Key* key = new Key(keys->size(), roomName, server, world);
    (*keys)[key->getID()] = key;
    RigidBody* body = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{data.roomPosition + data.position + data.relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, data.relativeMinCorner, data.relativeMaxCorner}, key, &world, true);

    key->setBody(body);
    return body;
}

