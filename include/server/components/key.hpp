#pragma once
#include <glm/glm.hpp>
#include "rigidBody.hpp"
#include <string>

class Server;

class Key : public ICustomPhysics {
  public:
    /**
     * @brief Constructs a Key object with a given ID and room name.
     *
     * @param id The unique identifier for the key.
     * @param room The name of the room where the key is located.
     * @param serverRef Reference to the Server instance for broadcasting messages.
     */
    Key(int id, std::string room, Server& serverRef);

    ~Key() = default;

    /**
     * @brief Returns the rigid body of the object.
     *
     * @return RigidBody* reference to the object's rigid body.
     */
    RigidBody* getBody();

    /**
     * @brief Sets the rigid body of the object.
     *
     * @param newBody The new rigid body to set.
     */
    void setBody(RigidBody* newBody);

    /**
     * @brief custom collision response of lilypad
     *
     * @param ptr to the object class that this object collided with
     */
    void customCollision(ICustomPhysics* otherObject) override;

    /**
     * @brief Returns the ID of the key.
     *
     * @return int ID of the key.
     */
    int getID() const;

    /**
     * @brief Returns the name of the room where the key is located.
     *
     * @return std::string Name of the room.
     */
    std::string getRoomName() const;

  private:
    int keyID;
    std::string roomName;
    RigidBody* body = nullptr;
    Server& server;
};
