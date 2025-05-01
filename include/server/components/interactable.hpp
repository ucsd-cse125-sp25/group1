#pragma once
#include "../rigidBody.hpp"

class Interactable
{
public:
	Interactable();
	// Todo: implement destructor
	virtual ~Interactable() = default;
	// Todo: add more functions
	void interact(); //handles the input that riggers the handle event. 

	/**
	 * @brief Returns a reference to the interactable's rigid body
	 *
	 * @return Reference to the interactable's associated RigidBody instance.
	 */
	RigidBody& getBody();

protected:
	virtual void handleInteract() = 0; //Pure virtual function, must be implemented by derived classes
};