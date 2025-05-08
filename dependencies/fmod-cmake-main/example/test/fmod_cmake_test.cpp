#include <fmod.hpp>
#include <fmod_errors.h>

#include <SDL.h>

#include <cstring>
#include <functional>
#include <iostream>
#include <thread>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>

// emscripten main loop
static std::function<void()> emMain;
static void runEmMain()
{
    emMain();
}
#endif

/// Check the result of an FMOD function, throw and report error if it did not succeed
/// @param result - result of the function
static void FMOD_CHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        std::cerr << "FMOD error on line " << __LINE__ << ": " << FMOD_ErrorString(result) << '\n';
        throw std::runtime_error(FMOD_ErrorString(result));
    }
}


int main(int argc, char *argv[])
{
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        std::cerr << "Failed to init SDL2: " << SDL_GetError() << '\n';
        return -1;
    }

    // Open window
    auto window = SDL_CreateWindow("Press 'P' to play blip sound",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 400, 0);
    if (!window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        return -1;
    }

#ifdef __EMSCRIPTEN__
    const auto renderFlags = 0;
#else
    const auto renderFlags = SDL_RENDERER_PRESENTVSYNC;
#endif
    auto renderer = SDL_CreateRenderer(window, -1, renderFlags);
    if (!renderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        return -1;
    }

    // Initialize fmod
    FMOD::System *sys;
    FMOD_CHECK(FMOD::System_Create(&sys));

    int samplerate;
    sys->getSoftwareFormat(&samplerate, nullptr, nullptr);
    sys->setSoftwareFormat(samplerate, FMOD_SPEAKERMODE_DEFAULT, 0);
    sys->setDSPBufferSize(256, 4);

    FMOD_CHECK(sys->init(1024, FMOD_INIT_NORMAL, nullptr));

    // Load sound
    FMOD::Sound *blip;
    FMOD_CHECK(sys->createSound("assets/blip.wav", 0, nullptr, &blip));

    std::cout << "Initialized program.\n";

    // Output instructions to user
    std::cout << "Press 'p' to play blip sound\n";

    // Let user know to interact with page to unblock audio
#ifdef __EMSCRIPTEN__
    std::cout << "When the platform is web browser, make a gesture on the page (e.g. clicking) to enable audio\n";
#endif

    // Input state
    uint8_t lastKeys[SDL_NUM_SCANCODES] = {0};
    const uint8_t *keys = SDL_GetKeyboardState(nullptr);

    // App state
    bool isRunning = true;

    // Main loop
#ifdef __EMSCRIPTEN__
    emMain = [&]() {
#else
    while(isRunning)
#endif
    {
        // Update event queue
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        // User controls
        if (keys[SDL_SCANCODE_P] && !lastKeys[SDL_SCANCODE_P])
        {
            sys->playSound(blip, nullptr, false, nullptr);
        }

        if (keys[SDL_SCANCODE_ESCAPE])
        {
            isRunning = false;
        }

        // Just render blank screen timed with VSync
        SDL_SetRenderDrawColor(renderer, 128, 128, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Apply audio engine updates
        FMOD_CHECK(sys->update());

        // Update last input state
        std::memcpy(lastKeys, keys, SDL_NUM_SCANCODES);
    }
#ifdef __EMSCRIPTEN__
    }; emscripten_set_main_loop(runEmMain, -1, 1);
#endif

    // Clean up
    blip->release();
    sys->release();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Shutdown complete.\n";
    return 0;
}
