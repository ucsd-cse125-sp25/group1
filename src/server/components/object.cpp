#include "components/object.hpp"

Object::Object(int id) : objectID(id) {}

RigidBody& Object::getBody() {
    return body;
}

void Object::setBody(RigidBody* newBody) {
    body = *newBody;
}

void Object::customCollision(ICustomPhysics* otherObject) {}
