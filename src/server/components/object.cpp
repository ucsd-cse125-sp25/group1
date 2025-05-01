#include "server/components/object.hpp"

Object::Object(int id, glm::vec3 position, glm::vec3 direction, float width, float height)
    : 
    id(id),
    body(
        vec3(0.0f),
        vec3(0.0f),
        0.0f, // mass of 0 - kinematics doesn't matter because it's static (imovable)
        new Transform { position, direction },
        new BoxCollider{
            AABB,
            vec3(-width / 2, -height / 2, -width / 2),
            vec3(width / 2, height / 2, width / 2)
        },
        true
    ) {}