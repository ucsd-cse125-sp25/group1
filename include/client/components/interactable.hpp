#pragma once

class Interactable
{
public:
    Interactable();
    virtual ~Interactable() = default;
    void interact(int playerID); //handles the input that riggers the handle event. 

    /**
     * @brief Sends message to server about what player is interacting with the object.
     * 
     * Gives information to the server about who is interacting with the object, 
     * alongside any additional necessary info. The server should have most of the logic of
     * how to determine the result of the interaction.
     * 
     * @param playerID the ID of the player who is interacting with the Interactable.
     */
    virtual void sendInteractRequest(int playerID) = 0; //Pure virtual function, must be implemented by derived classes
    
    /**
     * @brief Receives message from server about how to carry out an interaction.
     * 
     * Gets information from the server about the result of the interaction.
     * Then, this function should process that result and implement those changes
     * on the client.
     * 
     * @param state the binary state option for how the interaction should play out.
     * Any object will have at most 2 possibilities of what could happen
     * when interacting with it. This state encodes which of those possibilities that is.
     * If there is only one result of an interaction, state can be ignored.
     * Ex of state usage: Door needs to know if the interaction succeeds (can unlock and open)
     * or fails (remains locked). It has different results based on that success state.
     */
    virtual void processInteractResult(bool state) = 0; //Pure virtual function, must be implemented by derived classes
};