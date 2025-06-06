#include "scene.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <array>
#include <cctype>
#include <cmath>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

static const glm::mat4 I4{1.0f};

Scene::Scene(int playerID) : playerID(playerID) {}
Scene::~Scene() {}

void Scene::init() {
    shaders["character"] = std::make_unique<Shader>("../src/client/shaders/character.vert",
                                                    "../src/client/shaders/character.frag");

    shaders["model"] = std::make_unique<Shader>("../src/client/shaders/model.vert",
                                                "../src/client/shaders/model.frag");

    shaders["swamp"] = std::make_unique<Shader>("../src/client/shaders/model.vert",
                                                "../src/client/shaders/swamp.frag");

    uiShader =
        std::make_unique<Shader>("../src/client/shaders/ui.vert", "../src/client/shaders/ui.frag");

    lobbyAsset = std::make_unique<Model>("../src/client/models/lobby.obj");

    hotelRoomStraightX =
        std::make_unique<Model>("../src/client/models/1x1_hotel_room_straight_x.obj");
    hotelRoomStraightZ =
        std::make_unique<Model>("../src/client/models/1x1_hotel_room_straight_z.obj");

    hotelRoomTPosX = std::make_unique<Model>("../src/client/models/1x1_hotel_room_T_pos_x.obj");
    hotelRoomTNegX = std::make_unique<Model>("../src/client/models/1x1_hotel_room_T_neg_x.obj");

    hotelRoomBendPosXPosZ =
        std::make_unique<Model>("../src/client/models/1x1_hotel_room_bend_pos_x_pos_z.obj");
    hotelRoomBendPosXNegZ =
        std::make_unique<Model>("../src/client/models/1x1_hotel_room_bend_pos_x_neg_z.obj");
    hotelRoomBendNegXPosZ =
        std::make_unique<Model>("../src/client/models/1x1_hotel_room_bend_neg_x_pos_z.obj");
    hotelRoomBendNegXNegZ =
        std::make_unique<Model>("../src/client/models/1x1_hotel_room_bend_neg_x_neg_z.obj");

    hallwayX = std::make_unique<Model>("../src/client/models/1x1_hotel_hallway_x.obj");
    hallwayZ = std::make_unique<Model>("../src/client/models/1x1_hotel_hallway_z.obj");

    tableAsset = std::make_unique<Model>("../src/client/models/table.obj");
    doorAsset = std::make_unique<Model>("../src/client/models/door.obj");
    keyAsset = std::make_unique<Model>("../src/client/models/key.obj");

    swampRoomAsset = std::make_unique<Model>("../src/client/models/swamp_room.obj");
    lilypadAsset = std::make_unique<Model>("../src/client/models/lilypad.obj");
    frogAsset = std::make_unique<Model>("../src/client/models/froggie.obj");

    circusRoomAsset = std::make_unique<Model>("../src/client/models/tent.obj");
    cannonballAsset = std::make_unique<Model>("../src/client/models/cannonball.obj");
    cannonAsset = std::make_unique<Model>("../src/client/models/cannon.obj");

    pianoRoomAsset = std::make_unique<Model>("../src/client/models/piano_room.obj");

    lobbyAsset = std::make_unique<Model>("../src/client/models/lobby.obj");
    finalDoorAsset = std::make_unique<Model>("../src/client/models/final_door.obj");
    buttonBlueAsset = std::make_unique<Model>("../src/client/models/blue_button.obj");
    buttonPinkAsset = std::make_unique<Model>("../src/client/models/pink_button.obj");
    buttonYellowAsset = std::make_unique<Model>("../src/client/models/yellow_button.obj");
    buttonGreenAsset = std::make_unique<Model>("../src/client/models/green_button.obj");
    backPlateAsset = std::make_unique<Model>("../src/client/models/button_backplate.obj");

    canvas = std::make_unique<Canvas>();

    initRooms();
    initLights();
    initShadowMaps();

    renderStaticShadowPass();
    renderInteractableShadowPass();

    spawnFireflies(config::SWAMP_NUM_FIREFLIES);
}

void Scene::initRooms() {
    // Lobby (Room ID: 0)
    glm::mat4 lobbyModel = glm::translate(I4, config::LOBBY_POSITION);
    auto lobby = std::make_unique<ModelInstance>(lobbyAsset.get(), lobbyModel, nullptr, true);

    // glm::mat4 finalDoorLeftModel = glm::translate(I4, config::FINALDOOR_LEFT_POSITION);
    // finalDoorLeftModel =
    //     glm::rotate(finalDoorLeftModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // glm::mat4 finalDoorRightModel = glm::translate(I4, config::FINALDOOR_RIGHT_POSITION);
    // finalDoorRightModel =
    //     glm::rotate(finalDoorRightModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 finalDoorModel = glm::translate(I4, config::FINALDOOR_POSITION);
    finalDoorModel = glm::rotate(finalDoorModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    lobby->children["finalDoor"][0] =
        std::make_unique<ModelInstance>(finalDoorAsset.get(), finalDoorModel, lobby.get(), true);

    glm::mat4 blueButtonModel = glm::translate(I4, config::BUTTON_BLUE_POSITION);
    blueButtonModel =
        glm::rotate(blueButtonModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 pinkButtonModel = glm::translate(I4, config::BUTTON_PINK_POSITION);
    pinkButtonModel =
        glm::rotate(pinkButtonModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 yellowButtonModel = glm::translate(I4, config::BUTTON_YELLOW_POSITION);
    yellowButtonModel =
        glm::rotate(yellowButtonModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 greenButtonModel = glm::translate(I4, config::BUTTON_GREEN_POSITION);
    greenButtonModel =
        glm::rotate(greenButtonModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lobby->children["final_button"][0] =
        std::make_unique<ModelInstance>(buttonBlueAsset.get(), blueButtonModel, lobby.get(), true);
    lobby->children["final_button"][1] =
        std::make_unique<ModelInstance>(buttonPinkAsset.get(), pinkButtonModel, lobby.get(), true);
    lobby->children["final_button"][2] = std::make_unique<ModelInstance>(
        buttonYellowAsset.get(), yellowButtonModel, lobby.get(), true);
    lobby->children["final_button"][3] = std::make_unique<ModelInstance>(
        buttonGreenAsset.get(), greenButtonModel, lobby.get(), true);

    for (int i = 0; i < 4; ++i) {
        glm::mat4 backPlateModel = glm::translate(I4, config::BACK_PLATE_POSITIONS[i]);
        backPlateModel =
            glm::rotate(backPlateModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lobby->children["backPlate"][i] = std::make_unique<ModelInstance>(
            backPlateAsset.get(), backPlateModel, lobby.get(), true);
    }

    // Swamp room (Room ID: 1)
    glm::mat4 swampRoomModel = glm::translate(I4, config::SWAMP_ROOM_POSITION);
    auto swampRoom =
        std::make_unique<ModelInstance>(swampRoomAsset.get(), swampRoomModel, nullptr, true);

    for (int i = 0; i < config::SWAMP_NUM_LILYPADS; ++i) {
        glm::mat4 lilypadModel =
            glm::translate(I4, glm::vec3(22.0f + (i / 2) * 8.0f, 0.0f, ((i % 2) * -2 + 1) * 3.0f));

        float angleDegrees = fmod(i * 137.0f, 360.0f);
        lilypadModel =
            glm::rotate(lilypadModel, glm::radians(angleDegrees), glm::vec3(0.0f, 1.0f, 0.0f));

        swampRoom->children["lilypad"][i] = std::make_unique<ModelInstance>(
            lilypadAsset.get(), lilypadModel, swampRoom.get(), false);
    }

    glm::mat4 frogModel = glm::translate(I4, config::FROG_POSITION);
    frogModel = glm::rotate(frogModel, glm::radians(-120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    swampRoom->children["frog"][0] =
        std::make_unique<ModelInstance>(frogAsset.get(), frogModel, swampRoom.get(), true);

    // Swamp key room (Room ID: 2)
    glm::mat4 swampKeyRoomModel = glm::translate(I4, config::SWAMP_KEY_ROOM_POSITION);
    auto swampKeyRoom = std::make_unique<ModelInstance>(hotelRoomBendNegXPosZ.get(),
                                                        swampKeyRoomModel, nullptr, true);

    glm::mat4 swampKey = glm::translate(I4, config::SWAMP_KEY_POSITION);
    swampKey = glm::rotate(swampKey, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    swampKeyRoom->children["key"][0] =
        std::make_unique<ModelInstance>(keyAsset.get(), swampKey, swampKeyRoom.get(), false);

    glm::mat4 door1 = glm::rotate(I4, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    door1 = glm::translate(door1, glm::vec3(10.0f, 0.0f, 0.0f));
    swampKeyRoom->children["door"][0] =
        std::make_unique<ModelInstance>(doorAsset.get(), door1, swampKeyRoom.get(), false);

    // Circus room (Room ID: 3)
    glm::mat4 circusRoomModel = glm::translate(I4, config::CIRCUS_ROOM_POSITION);
    auto circusRoom =
        std::make_unique<ModelInstance>(circusRoomAsset.get(), circusRoomModel, nullptr, true);

    for (int i = 0; i < config::NUM_CANNONBALLS; i++) {
        // init cannon
        glm::mat4 cannon = glm::translate(I4, config::CANNONBALL_POSITIONS[i]);
        cannon = glm::translate(cannon, {5.0f, 0.0f, 0.0f});
        circusRoom->children["cannon"][i] =
            std::make_unique<ModelInstance>(cannonAsset.get(), cannon, circusRoom.get());
        // init cannonball
        glm::mat4 cannonball = glm::translate(I4, config::CANNONBALL_POSITIONS[i]);
        circusRoom->children["cannonball"][i] = std::make_unique<ModelInstance>(
            cannonballAsset.get(), cannonball, circusRoom.get(), false);
    }

    // Circus key room (Room ID: 4)
    glm::mat4 circusKeyRoomModel = glm::translate(I4, config::CIRCUS_KEY_ROOM_POSITION);
    auto circusKeyRoom = std::make_unique<ModelInstance>(hotelRoomBendNegXPosZ.get(),
                                                         circusKeyRoomModel, nullptr, true);

    glm::mat4 door3 = glm::rotate(I4, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    door3 = glm::translate(door3, glm::vec3(10.0f, 0.0f, 0.0f));
    circusKeyRoom->children["door"][0] =
        std::make_unique<ModelInstance>(doorAsset.get(), door3, circusKeyRoom.get(), false);

    // Piano room (Room ID: 5)
    glm::mat4 pianoRoomModel = glm::translate(I4, config::PIANO_ROOM_POSITION);
    auto pianoRoom =
        std::make_unique<ModelInstance>(pianoRoomAsset.get(), pianoRoomModel, nullptr, true);

    // Parkour room (Room ID: 6)
    glm::mat4 parkourKeyRoomModel = glm::translate(I4, config::PARKOUR_ROOM_POSITION);
    auto parkourKeyRoom =
        std::make_unique<ModelInstance>(hotelRoomBendNegXPosZ.get(), parkourKeyRoomModel);
    glm::mat4 parkourKey = glm::translate(I4, config::PARKOUR_KEY_POSITION);
    parkourKeyRoom->children["key"][0] =
        std::make_unique<ModelInstance>(keyAsset.get(), parkourKey, parkourKeyRoom.get(), false);

    std::array<Model*, 3> parkourObjects = {tableAsset.get(), tableAsset.get(), tableAsset.get()};

    for (int i = 0; i < 3; ++i) {
        glm::mat4 parkourObject = glm::translate(I4, config::PARKOUR_OBJECT_POSITIONS[i]);
        parkourKeyRoom->children["objects"][i] =
            std::make_unique<ModelInstance>(parkourObjects[i], parkourObject, parkourKeyRoom.get());
    }

    // Hotel rooms (Room IDs: 7 - 21)
    std::array<glm::mat4, 15> hotelRoomModels;
    std::array<std::unique_ptr<ModelInstance>, 15> hotelRooms;

    std::array<Model*, 15> hotelRoomVariants = {
        hotelRoomBendPosXPosZ.get(), hotelRoomBendPosXNegZ.get(), hotelRoomBendPosXNegZ.get(),
        hotelRoomTNegX.get(),        hotelRoomBendNegXNegZ.get(), hotelRoomBendPosXPosZ.get(),
        hotelRoomTPosX.get(),        hotelRoomBendPosXNegZ.get(), hotelRoomBendPosXPosZ.get(),
        hotelRoomStraightZ.get(),    hotelRoomBendNegXNegZ.get(), hotelRoomBendNegXPosZ.get(),
        hotelRoomBendPosXNegZ.get(), hotelRoomStraightX.get(),    hotelRoomTPosX.get()};

    for (int i = 0; i < 15; ++i) {
        hotelRoomModels[i] = glm::translate(I4, config::HOTEL_ROOM_POSITIONS[i]);
        hotelRooms[i] = std::make_unique<ModelInstance>(hotelRoomVariants[i], hotelRoomModels[i],
                                                        nullptr, true);
    }

    // Hotel room 0 (Room ID: 7)
    glm::mat4 tableModel = glm::translate(I4, config::TABLE_POSITION);
    hotelRooms[0]->children["table"][0] =
        std::make_unique<ModelInstance>(tableAsset.get(), tableModel, hotelRooms[0].get(), true);

    glm::mat4 door0 = glm::rotate(I4, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    door0 = glm::translate(door0, glm::vec3(10.0f, 0.0f, 0.0f));
    hotelRooms[0]->children["door"][0] =
        std::make_unique<ModelInstance>(doorAsset.get(), door0, hotelRooms[0].get(), false);

    // Hotel room 5 (Room ID: 12)
    glm::mat4 door2 = glm::rotate(I4, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    door2 = glm::translate(door2, glm::vec3(10.0f, 0.0f, 0.0f));
    hotelRooms[5]->children["door"][0] =
        std::make_unique<ModelInstance>(doorAsset.get(), door2, hotelRooms[5].get(), false);

    // Hotel room 14 (Room ID: 21)
    glm::mat4 door4 = glm::rotate(I4, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    door4 = glm::translate(door4, glm::vec3(10.0f, 0.0f, 0.0f));
    hotelRooms[14]->children["door"][0] =
        std::make_unique<ModelInstance>(doorAsset.get(), door4, hotelRooms[14].get(), false);

    // Hallways (Room IDs: 22 - 28)
    std::array<glm::mat4, 7> hallwayModels;
    std::array<std::unique_ptr<ModelInstance>, 7> hallways;

    std::array<Model*, 7> hallwayVariants = {hallwayZ.get(), hallwayX.get(), hallwayX.get(),
                                             hallwayZ.get(), hallwayZ.get(), hallwayX.get(),
                                             hallwayZ.get()};

    for (int i = 0; i < 7; ++i) {
        hallwayModels[i] = glm::translate(I4, config::HOTEL_HALLWAY_POSITIONS[i]);
        hallways[i] =
            std::make_unique<ModelInstance>(hallwayVariants[i], hallwayModels[i], nullptr, true);
    }

    modelInstances["lobby"] = std::move(lobby);
    modelInstances["swampRoom"] = std::move(swampRoom);
    modelInstances["swampKeyRoom"] = std::move(swampKeyRoom);
    modelInstances["circusRoom"] = std::move(circusRoom);
    modelInstances["circusKeyRoom"] = std::move(circusKeyRoom);
    modelInstances["pianoRoom"] = std::move(pianoRoom);
    modelInstances["parkourKeyRoom"] = std::move(parkourKeyRoom);

    for (int i = 0; i < 15; ++i) {
        modelInstances["hotelRoom" + std::to_string(i)] = std::move(hotelRooms[i]);
    }

    for (int i = 0; i < 7; ++i) {
        modelInstances["hallway" + std::to_string(i)] = std::move(hallways[i]);
    }

    roomNames = {"lobby",         "swampRoom", "swampKeyRoom",  "circusRoom",
                 "circusKeyRoom", "pianoRoom", "parkourKeyRoom"};

    for (int i = 0; i < 15; ++i) {
        roomNames.push_back("hotelRoom" + std::to_string(i));
    }

    for (int i = 0; i < 7; ++i) {
        roomNames.push_back("hallway" + std::to_string(i));
    }

    connectedRooms["lobby"] = {"hotelRoom3",  "hotelRoom4", "hotelRoom6", "hotelRoom7",
                               "hotelRoom10", "hallway2",   "hallway3",   "hallway4"};
    connectedRooms["swampRoom"] = {"swampKeyRoom", "hotelRoom0", "hallway0", "hallway3"};
    connectedRooms["swampKeyRoom"] = {"swampRoom", "hotelRoom0", "hotelRoom3", "hotelRoom4",
                                      "hallway3"};
    connectedRooms["circusRoom"] = {"circusKeyRoom", "hotelRoom5", "hallway4", "hallway6"};
    connectedRooms["circusKeyRoom"] = {"circusRoom", "pianoRoom", "hotelRoom5", "hotelRoom14",
                                       "hallway6"};
    connectedRooms["pianoRoom"] = {"circusKeyRoom", "hotelRoom13", "hotelRoom14", "hallway6"};
    connectedRooms["parkourKeyRoom"] = {"hotelRoom1", "hotelRoom2", "hallway0", "hallway1"};
    connectedRooms["hotelRoom0"] = {"swampRoom", "swampKeyRoom", "hotelRoom1", "hallway0"};
    connectedRooms["hotelRoom1"] = {"parkourKeyRoom", "hotelRoom0", "hotelRoom2", "hallway0",
                                    "hallway1"};
    connectedRooms["hotelRoom2"] = {"parkourKeyRoom", "hotelRoom1", "hotelRoom4",
                                    "hallway0",       "hallway1",   "hallway2"};
    connectedRooms["hotelRoom3"] = {"lobby",      "swampKeyRoom", "hotelRoom4",
                                    "hotelRoom6", "hallway2",     "hallway3"};
    connectedRooms["hotelRoom4"] = {"lobby",    "swampKeyRoom", "hotelRoom2", "hotelRoom3",
                                    "hallway1", "hallway2",     "hallway3"};
    connectedRooms["hotelRoom5"] = {"circusRoom", "circusKeyRoom", "hotelRoom6", "hotelRoom7",
                                    "hallway4"};
    connectedRooms["hotelRoom6"] = {"lobby",      "hotelRoom3",  "hotelRoom5",
                                    "hotelRoom7", "hotelRoom10", "hallway4"};
    connectedRooms["hotelRoom7"] = {"lobby",      "hotelRoom5",  "hotelRoom6",
                                    "hotelRoom9", "hotelRoom10", "hallway4"};
    connectedRooms["hotelRoom8"] = {"hotelRoom9", "hotelRoom10", "hotelRoom11", "hallway5"};
    connectedRooms["hotelRoom9"] = {"hotelRoom7", "hotelRoom8", "hotelRoom10", "hallway5"};
    connectedRooms["hotelRoom10"] = {"lobby", "hotelRoom6", "hotelRoom7", "hotelRoom8",
                                     "hotelRoom9"};
    connectedRooms["hotelRoom11"] = {"hotelRoom8", "hotelRoom12", "hotelRoom13", "hallway5"};
    connectedRooms["hotelRoom12"] = {"hotelRoom11", "hotelRoom13", "hotelRoom14", "hallway5"};
    connectedRooms["hotelRoom13"] = {"pianoRoom",   "hotelRoom11", "hotelRoom12",
                                     "hotelRoom14", "hallway5",    "hallway6"};
    connectedRooms["hotelRoom14"] = {"circusKeyRoom", "pianoRoom", "hotelRoom12", "hotelRoom13",
                                     "hallway6"};
    connectedRooms["hallway0"] = {"swampRoom",  "parkourKeyRoom", "hotelRoom0",
                                  "hotelRoom1", "hotelRoom2",     "hallway1"};
    connectedRooms["hallway1"] = {"parkourKeyRoom", "hotelRoom1", "hotelRoom2",
                                  "hotelRoom4",     "hallway0",   "hallway2"};
    connectedRooms["hallway2"] = {"lobby", "hotelRoom2", "hotelRoom3", "hotelRoom4", "hallway1"};
    connectedRooms["hallway3"] = {"lobby", "swampRoom", "swampKeyRoom", "hotelRoom3", "hotelRoom4"};
    connectedRooms["hallway4"] = {"lobby", "circusRoom", "hotelRoom5", "hotelRoom6", "hotelRoom7"};
    connectedRooms["hallway5"] = {"hotelRoom8", "hotelRoom9", "hotelRoom11", "hotelRoom12",
                                  "hotelRoom13"};
    connectedRooms["hallway6"] = {"circusRoom", "circusKeyRoom", "pianoRoom", "hotelRoom13",
                                  "hotelRoom14"};
}

void Scene::initLights() {
    pointLights["lobby"] = {PointLight(glm::translate(I4, config::LOBBY_POSITION),
                                       glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["swampRoom"] = {PointLight(glm::translate(I4, config::SWAMP_ROOM_POSITION),
                                           glm::vec3(30.0f, 7.0f, 0.0f), glm::vec3(0.7f)),
                                PointLight(glm::translate(I4, config::SWAMP_ROOM_POSITION),
                                           glm::vec3(70.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["swampKeyRoom"] = {PointLight(glm::translate(I4, config::SWAMP_KEY_ROOM_POSITION),
                                              glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["circusRoom"] = {PointLight(glm::translate(I4, config::CIRCUS_ROOM_POSITION),
                                            glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["circusKeyRoom"] = {PointLight(glm::translate(I4, config::CIRCUS_KEY_ROOM_POSITION),
                                               glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["pianoRoom"] = {PointLight(glm::translate(I4, config::PIANO_ROOM_POSITION),
                                           glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    pointLights["parkourKeyRoom"] = {PointLight(glm::translate(I4, config::PARKOUR_ROOM_POSITION),
                                                glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};

    for (int i = 0; i < 15; ++i) {
        pointLights["hotelRoom" + std::to_string(i)] = {
            PointLight(glm::translate(I4, config::HOTEL_ROOM_POSITIONS[i]),
                       glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    }

    for (int i = 0; i < 7; ++i) {
        pointLights["hallway" + std::to_string(i)] = {
            PointLight(glm::translate(I4, config::HOTEL_HALLWAY_POSITIONS[i]),
                       glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(1.0f))};
    }
}

void Scene::initShadowMaps() {
    for (const auto& [name, lights] : pointLights) {
        for (const PointLight& light : lights) {
            auto staticShadowMap =
                std::make_unique<ShadowMap>(light.worldPosition, config::SHADOW_MAP_RES_STATIC);
            staticShadowMaps[name].emplace_back(std::move(staticShadowMap));

            auto interactableShadowMap = std::make_unique<ShadowMap>(
                light.worldPosition, config::SHADOW_MAP_RES_INTERACTABLE);
            interactableShadowMaps[name].emplace_back(std::move(interactableShadowMap));
            interactableShadowActive[name].emplace_back(false);

            auto playerShadowMap =
                std::make_unique<ShadowMap>(light.worldPosition, config::SHADOW_MAP_RES_PLAYER);
            playerShadowMaps[name].emplace_back(std::move(playerShadowMap));
            playerShadowActive[name].emplace_back(false);
        }
    }
}

void Scene::updatePlayerState(int id, const glm::vec3& position, const glm::vec3& direction) {
    if (!players.contains(id)) {
        auto [it, inserted] = players.emplace(id, Player(id, position, direction));
        if (inserted) {
            it->second.init();
        }
    } else {
        players.at(id).setPosition(position);
        players.at(id).setDirection(direction);
    }
}

void Scene::updateWindow() {
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    canvas->updateWindow(width, height);
}

void Scene::removePlayer(int id) {
    players.erase(id);
}

void Scene::removeInstanceFromRoom(const std::string& roomName, const std::string& type, int id) {
    modelInstances[roomName]->deleteChild(type, id);
}

void Scene::removeDoor(int id) {
    if (id == 0) {
        removeInstanceFromRoom("hotelRoom0", "door", 0);
    } else if (id == 1) {
        removeInstanceFromRoom("swampKeyRoom", "door", 0);
    } else if (id == 2) {
        removeInstanceFromRoom("hotelRoom5", "door", 0);
    } else if (id == 3) {
        removeInstanceFromRoom("circusKeyRoom", "door", 0);
    } else if (id == 4) {
        removeInstanceFromRoom("hotelRoom14", "door", 0);
    }
}

void Scene::addKeyToSlot(const std::string& roomName, const std::string& type, int id) {
    glm::mat4 keyModel = glm::translate(I4, config::FINALDOOR_KEY_SLOTS[id]);
    keyModel = glm::rotate(keyModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    modelInstances[roomName]->children[type][id] = std::make_unique<ModelInstance>(
        keyAsset.get(), keyModel, modelInstances[roomName].get(), true);
}

void Scene::moveChildTransform(const std::string& roomName, const std::string& type, int id,
                               const glm::vec3& offset) {

    auto& room = modelInstances[roomName];
    // if (!room || !room->children.contains(type) || !room->children[type].contains(id))
    //     return;

    auto& child = room->children[type][id];
    // Apply translation to the existing localTransform
    child->translateLocal(offset);
}

void Scene::renderStaticShadowPass() {
    for (auto& [name, shadowMaps] : staticShadowMaps) {
        for (const auto& shadowMap : shadowMaps) {
            shadowMap->begin();

            Shader& shader = shadowMap->getShader();
            shader.setBool("isSkinned", false);
            modelInstances[name]->drawRecursive(shader, false, true);

            shadowMap->end();
        }
    }
}

void Scene::renderInteractableShadowPass() {
    renderLilypadShadowPass();

    // Add "circusKeyRoom", "pianoKeyRoom" later
    std::vector<std::string> keyRooms = {"swampKeyRoom", "parkourKeyRoom"};
    for (const std::string& roomName : keyRooms) {
        auto& shadowMaps = interactableShadowMaps[roomName];
        shadowMaps[0]->begin();

        Shader& shader = shadowMaps[0]->getShader();
        shader.setBool("isSkinned", false);
        modelInstances[roomName]->drawInteractable(shader, "key");

        shadowMaps[0]->end();
        interactableShadowActive[roomName][0] = true;
    }
}

void Scene::renderPlayerShadowPass() {
    std::unordered_map<std::string, std::vector<Player*>> playersByRoom;

    for (auto& [id, player] : players) {
        int roomID = player.getCurrRoomID();
        std::string roomName = roomNames[roomID];
        playersByRoom[roomName].push_back(&player);
    }

    for (auto& [roomName, playersInRoom] : playersByRoom) {
        auto& shadowMaps = playerShadowMaps[roomName];

        for (int i = 0; i < shadowMaps.size(); ++i) {
            shadowMaps[i]->begin();

            Shader& shader = shadowMaps[i]->getShader();
            shader.setBool("isSkinned", true);

            for (Player* player : playersInRoom) {
                player->draw(shader);
            }

            shadowMaps[i]->end();
            playerShadowActive[roomName][i] = true;
        }
    }

    for (const std::string& roomName : roomNames) {
        if (!playersByRoom.contains(roomName)) {
            for (int i = 0; i < playerShadowMaps[roomName].size(); ++i) {
                playerShadowActive[roomName][0] = false;
            }
        }
    }
}

void Scene::spawnFireflies(int count) {
    glm::vec3 center = config::SWAMP_ROOM_POSITION + glm::vec3(50.0f, 5.0f, 0.0f);
    glm::vec3 half = glm::vec3(35.0f, 5.0f, 30.0f);

    for (int i = 0; i < count; ++i) {
        glm::vec3 position = center + glm::linearRand(-half, half);
        glm::vec3 direction = glm::sphericalRand(1.0f);
        float speed = glm::linearRand(0.5f, 1.5f);

        fireflies.emplace_back(position, direction, speed, center, half);
    }
}

void Scene::renderLilypadShadowPass(int id) {
    auto& shadowMaps = interactableShadowMaps["swampRoom"];

    auto renderForIndex = [&](int index) {
        shadowMaps[index]->begin();
        Shader& shader = shadowMaps[index]->getShader();
        shader.setBool("isSkinned", false);

        int start = (index == 0) ? 0 : 8;
        int end = (index == 0) ? 7 : 15;
        modelInstances["swampRoom"]->drawInteractable(shader, "lilypad", start, end);

        shadowMaps[index]->end();
    };

    if (id == -1) {
        for (int i = 0; i < 2; ++i) {
            renderForIndex(i);
            interactableShadowActive["swampRoom"][i] = true;
        }
    } else {
        renderForIndex((id < 8) ? 0 : 1);
    }
}

/**
 * Takes in an array of NUM_CANNONBALLS cannonball positions.
 * For each position, sets the ith cannonball to the ith position.
 */
void Scene::updateCannonballPositions(glm::vec3 positions[]) {
    auto it = modelInstances.find("circusRoom");
    if (it == modelInstances.end())
        return;
    ModelInstance* circusRoomInstance = it->second.get();

    glm::vec3 roomOffset = config::CIRCUS_ROOM_POSITION;
    static const glm::mat4 I4{1.0f};

    auto& cannonBalls = circusRoomInstance->children["cannonball"];
    for (int i = 0; i < config::NUM_CANNONBALLS; ++i) {
        if (i >= static_cast<int>(cannonBalls.size()) || !cannonBalls[i])
            continue;
        ModelInstance* ballInst = cannonBalls[i].get();

        // Convert server’s “absolute” position into a room‐local offset:
        glm::vec3 localPos = positions[i] - roomOffset;
        glm::mat4 newLocal = glm::translate(I4, localPos);
        ballInst->localTransform = newLocal;
    }
}

void Scene::render(const Camera& camera, bool boundingBoxMode) {
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    renderPlayerShadowPass();

    shaders["character"]->use();

    for (auto& [id, player] : players) {
        if (id == playerID)
            continue;

        int roomID = player.getCurrRoomID();
        std::string roomName = roomNames[roomID];
        int numLights = pointLights[roomName].size();

        shaders["character"]->setInt("numLights", numLights);
        for (int i = 0; i < numLights; ++i) {
            shaders["character"]->setVec3("pointLights[" + std::to_string(i) + "].position",
                                          pointLights[roomName][i].worldPosition);
            shaders["character"]->setVec3("pointLights[" + std::to_string(i) + "].color",
                                          pointLights[roomName][i].color);
        }

        player.updateTime(deltaTime);
        player.draw(*shaders["character"]);
    }

    for (auto& [name, shader] : shaders) {
        shader->use();

        shader->setMat4("view", camera.getViewMatrix());
        shader->setMat4("projection", camera.getProjectionMatrix());
        shader->setVec3("viewPos", camera.getPosition());

        if (name == "character") {
            continue;
        }

        for (int i = 0; i < 6; ++i) {
            shader->setInt("shadowDepthCubemap" + std::to_string(i),
                           config::SHADOW_TEXTURE_UNIT + i);
        }

        shader->setFloat("shadowFarClip", config::SHADOW_FAR_CLIP);
    }

    // Draw all visible rooms in the scene
    for (const auto& [name, instance] : modelInstances) {
        if (players.contains(playerID)) {
            int currentRoomID = players.at(playerID).getCurrRoomID();

            if (!connectedRooms[roomNames[currentRoomID]].contains(name) &&
                name != roomNames[currentRoomID]) {
                continue;
            }
        }

        Shader* shader = nullptr;
        const auto& lights = pointLights[name];

        for (int i = 0; i < 2; ++i) {
            glActiveTexture(GL_TEXTURE0 + config::SHADOW_TEXTURE_UNIT + i);
            GLuint tex = (i < lights.size()) ? staticShadowMaps[name][i]->getDepthCubemap()
                                             : getDummyCubemap();
            glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

            glActiveTexture(GL_TEXTURE0 + config::SHADOW_TEXTURE_UNIT + i + 2);
            tex = i < (lights.size()) ? interactableShadowMaps[name][i]->getDepthCubemap()
                                      : getDummyCubemap();
            glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

            glActiveTexture(GL_TEXTURE0 + config::SHADOW_TEXTURE_UNIT + i + 4);
            tex = i < (lights.size()) ? playerShadowMaps[name][i]->getDepthCubemap()
                                      : getDummyCubemap();
            glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
        }

        if (name.starts_with("hotelRoom") || name.ends_with("KeyRoom") ||
            name.starts_with("hallway")) {
            shader = shaders["model"].get();
            shader->use();
            shader->setBool("useFade", false);
        } else if (name == "swampRoom") {
            shader = shaders["swamp"].get();
            shader->use();
            shader->setBool("useFog", true);
            shader->setVec3("fogColor", glm::vec3(0.05f, 0.07f, 0.1f));
            shader->setFloat("fogStart", 10.0f);
            shader->setFloat("fogEnd", 60.0f);
        } else if (name == "lobby" || name == "circusRoom" || name == "pianoRoom") {
            shader = shaders["model"].get();
            shader->use();
            shader->setBool("useFade", true);
        }

        shader->setInt("numLights", lights.size());

        for (int i = 0; i < lights.size(); ++i) {
            shader->setVec3("pointLights[" + std::to_string(i) + "].position",
                            lights[i].worldPosition);
            shader->setVec3("pointLights[" + std::to_string(i) + "].color", lights[i].color);
            shader->setBool("interactableShadowActive[" + std::to_string(i) + "]",
                            interactableShadowActive[name][i]);
            shader->setBool("playerShadowActive[" + std::to_string(i) + "]",
                            playerShadowActive[name][i]);
        }

        if (name == "lobby") {
            // glEnable(GL_BLEND);
            // glDepthMask(GL_FALSE);
            // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            instance->drawRecursive(*shader, boundingBoxMode);

            // glDepthMask(GL_TRUE);
            // glDisable(GL_BLEND);
        } else {
            instance->drawRecursive(*shader, boundingBoxMode);
        }
    }

    for (Firefly& firefly : fireflies) {
        firefly.update(deltaTime);
    }

    fireflyRenderer.draw(fireflies, camera.getViewMatrix(), camera.getProjectionMatrix());

    // UI
    updateWindow();
    canvas->draw(*uiShader);
}

void Scene::setPlayerRoomID(int clientID, int roomID) {
    if (players.contains(clientID)) {
        players.at(clientID).setCurrRoomID(roomID);
    }
}

int Scene::getPlayerRoomID(int clientID) {
    if (players.contains(clientID)) {
        return players.at(clientID).getCurrRoomID();
    }

    return -1;
}

void Scene::setPlayerState(int clientID, int state) {
    if (players.contains(clientID)) {
        players.at(clientID).setState(state);
    }
}
