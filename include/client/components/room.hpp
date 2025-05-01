#pragma once
#include <vector>
#include <string>

class Room
{
public:
	Room(int id);
	~Room();

	//// Todo: add room functions and attributes
	//void addInteractable(Interactable* object);
	//void removeInteractable(Interactable* object);

	int getID() const;
	//std::string getName() const;
	//const std::vector<Interactable*>& getInteractables() const;



private:
	// Todo: add member variables
	int roomID;

	////TODO: do we need rooname?
	//std::string roomName;
	//// Todo: change these interactable pointers to unique_ptr rather than normal pointers to prevent mem leaks and make ownership clear
	//std::vector<Interactable*> interactables;


	//Note: list of object would be if physics ever does room specific collisions detection. 
	// Potentially when object added to world 



	//client side objects and interactables has member field ID to help server know which one it is 
	//server object will need id field 
};