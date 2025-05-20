#include <algorithm>
#include "components/room.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "components/room.hpp"
#include "config.hpp"


Room::Room(int id, const std::string& name, Model* roomModel, Model* doorModel)
    : roomID(id), roomName(name)
{
    hotelRoomAsset = std::make_unique<Model>("../src/client/models/1x1_hotel_room.obj");
    // Todo: any additional initialization (i.e. doors) if needed
    const glm::mat4 I4{1.0f};
    glm::mat4 roomTransform = glm::translate(I4, config::HOTEL_ROOM_POSITION);
    modelRoot = std::make_unique<ModelInstance>(hotelRoomAsset.get(), roomTransform);

    // Add table
    // glm::mat4 tableTransform = glm::translate(I4, config::TABLE_POSITION);
    // modelRoot->addChild("table", 0, std::make_unique<ModelInstance>(tableModel, tableTransform, modelRoot.get()));

    // Add 3 doors
    std::array<float, 3> degrees = {90.0f, 180.0f, 270.0f};
    for (int i = 0; i < degrees.size(); ++i) {
        glm::mat4 doorTransform = glm::rotate(I4, glm::radians(degrees[i]), glm::vec3(0.0f, 1.0f, 0.0f));
        doorTransform = glm::translate(doorTransform, glm::vec3(10.0f, 0.0f, 0.0f));
        modelRoot->children["door"][i] =
            std::make_unique<ModelInstance>(doorModel, doorTransform, modelRoot.get());
    }

}

Room::~Room(){
    // Nothing todo yet; free any dynamically allocated in the future if added.
}

int Room::getID() const{
    return roomID;
}

std::string Room::getName() const{
    return roomName;
}

void Room::addInteractable(std::unique_ptr<Interactable> object) {
    interactables.push_back(std::move(object));
}

// return a vector of raw pointers for read-only access
std::vector<Interactable*> Room::getInteractables() const {
    std::vector<Interactable*> out;
    out.reserve(interactables.size());
    for (auto& uptr : interactables)
        out.push_back(uptr.get());
    return out;
}

void Room::removeInteractable(Interactable* object) {
    auto it = std::remove_if(
      interactables.begin(),
      interactables.end(),
      [object](auto const& up) { return up.get() == object; }
    );
    interactables.erase(it, interactables.end());
  }

ModelInstance* Room::getModelInstanceRoot() const {
    return modelRoot.get();
}

void Room::addVisualObject(const std::string& type, int index, Model* model, glm::mat4 objectTransform) {
    //Make a addChild function for dynamic object creation?
    //Will this be handled by the server?
    modelRoot->children[type][index] = std::make_unique<ModelInstance>(model, objectTransform, modelRoot.get());
}