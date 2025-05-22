#include "components/object.hpp"

Object::Object(int id, const glm::vec3& position, const glm::vec3& direction, float width,
               float height)
    : objectID(id),
      body(glm::vec3(0.0f), glm::vec3(0.0f),
           0.0f, // mass of 0 - kinematics doesn't matter because it's static (imovable)
           new Transform{position, direction},
           new BoxCollider{
               AABB,
               // TODO: add depth so it works with rectangulary prisms too, not just cubes.
               glm::vec3(-width / 2, -height / 2, -width / 2),
               glm::vec3(width / 2, height / 2, width / 2)},
           this, // refernce to interface
           true) {}

RigidBody& Object::getBody() {
    return body;
}

void Object::customCollision(ICustomPhysics* otherObject) {}
