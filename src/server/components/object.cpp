#include "components/object.hpp"

Object::Object(int id) : Object(id, nullptr) {}

Object::Object(int id, CollisionCallback func) : objectID(id), func(func) {}

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

void Object::customCollision(ICustomPhysics* otherObject) {
    if (func) {
        func(otherObject);
    }
}
