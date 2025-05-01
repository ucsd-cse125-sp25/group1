#pragma once

#include <vector>
#include <array>
#include "components/room.hpp"
#include "components/interactable.hpp"

class Swamp : public Room {
public:
	/**
	* @brief Constructs a Swamp instance.
	*
	* Initializes the swamp
	*/
	Swamp(int roomID);

	/**
	 * @brief Destructor for Swamp.
	 */
	~Swamp();

	/**
	  * @brief Initializes the swamp game on the server side
	  *
	  * Sets up the game state, including the number of pads and their initial states.
	  *
	  * @return true if the game was initialized successfully, false otherwise.
	  */
	bool init();


	/**
	 * @brief Returns the game initialization information client side needs in a packet
	 *
	 * @return A JSON string containing the game initialization information.
	 *
	 * Example JSON:
	 * {
	 *     "type": "swampInit",
	 *     "roomID": 1,
	 *     "numPads": 4,
	 *     "gameState": "waiting",
	 *     "audioFile": "swamp_audio.mp3"
	 * }
	 */
	std::string getInitInfo();


	/**
	 * @brief The game state of the swamp game
	 *
	 * @return A vector of pairs representing the game state of the swamp game.
	 */
	std::vector<std::array<int, 2>> getGameState();




private:
	/**
	 * @brief Number of pads in the swamp game
	 */
	int numPads;

	/**
	 * @brief Current game state of the swamp game
	 *
	 * A vector of length numPads of pairs, each element is either 0 (lilypad has sunk) or 1 (lilypad is rendered).
	 */
	std::vector<std::array<int, 2>> gameState;

	//add in objects.
	//std::vector<std::array<OBjects*, 2>> pads;

	std::vector<Interactable*>  frogs;

	/**
	  *  @brief Solution Key to the Swamp Game
	  *
	  * A vector, where each element is 0 or 1 representing, the correct lilpad for that step [index] .
	  */
	std::vector<int> soluiton;

	//handleFrog'
		//server determines which audio files to play

	//two arrary in config 1 for list of solutions 1 for list of audio fiels
	// swamp creation of frog pass over the audio solution
};