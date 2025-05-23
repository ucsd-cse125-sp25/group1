RigidBody* initObject() {
    // Default object creation
    object = new RigidBody(vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{roomPosition + position + relativePosition, vec3(0.0f)},
        new BoxCollider{AABB, relativeMinCorner, relativeMaxCorner}, nullptr, true);
}

RigidBody* initDoor() {
    
}

RigidBody* initFrog() {
    
}

RigidBody* initLilyPad() {
    auto [lilyPad, colliderType] = swamp->createLilyPad();

    object = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{roomPosition + position + relativePosition, vec3(0.0f)},
        new BoxCollider{colliderType, relativeMinCorner, relativeMaxCorner}, lilyPad, true);

    lilyPad->setBody(object);
}

RigidBody* initWater() {
    Water* waterRespawnPlane = swamp->createWaterRespawn();
    // TODO: add the position/relative position in the json dimensions file
    object = new RigidBody(
        vec3(0.0f), vec3(0.0f), 0.0f,
        new Transform{roomPosition + position + relativePosition, vec3(0.0f)},
        new BoxCollider{NONE, relativeMinCorner, relativeMaxCorner}, waterRespawnPlane, true);
    waterRespawnPlane->setBody(object);
}