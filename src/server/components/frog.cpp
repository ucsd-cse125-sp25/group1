#include "components/frog.hpp"
#include "json.hpp"
#include "server.hpp"
#include "swamp.hpp"

using json = nlohmann::json;

Frog::Frog(int id, Swamp* swampRef) : Interactable(id), swamp(swampRef) {}

void Frog::handleInteract(const Player& player) {
    // Define behavior here
    json message;
    message["type"] = "sfx";
    message["sfx_id"] = config::SWAMP_AUDIO_FILE;
    message["client_id"] = player.getID();
    message["action"] = "interact";
    message["volume"] = config::SWAMP_AUDIO_FILE_VOL;

    std::string packet = message.dump() + "\n";
    swamp->getServer().broadcastMessage(packet);
}
