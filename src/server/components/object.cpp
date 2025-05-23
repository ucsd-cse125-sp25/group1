#include "components/object.hpp"

Object::Object(int id) : objectID(id) {}

int Object::getID() const {
    return objectID;
}

RigidBody* Object::getBody() {
    return body;
}

void Object::setBody(RigidBody* newBody) {
    if (newBody == nullptr)
        return;
    body = newBody;
}

void Object::customCollision(ICustomPhysics* otherObject) {}
