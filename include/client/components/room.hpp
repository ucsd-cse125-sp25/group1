#pragma once
#include <vector>
#include <string>
#include <memory> 
#include "components/interactable.hpp"
#include "modelInstance.hpp"

class Room
{
public:
    Room(int id, const std::string& name = "Room", Model* roomModel = nullptr, Model* doorModel = nullptr);
    ~Room();
    void addInteractable(std::unique_ptr<Interactable> object);
    void removeInteractable(Interactable* object);

    int getID() const;
    std::string getName() const;
    std::vector<Interactable*> getInteractables() const;

    ModelInstance* getModelInstanceRoot() const; 
    void addVisualObject(const std::string& type, int index, Model* model, glm::mat4 objectTransform);


    
private:
    int roomID;
    std::string roomName;
    std::vector<std::unique_ptr<Interactable>> interactables;

    std::unique_ptr<ModelInstance> modelRoot;
    std::unique_ptr<Model> hotelRoomAsset;
};