/// 
/// @file audioEngine.cpp
/// @author Ross Hoyt
///
#include "audioEngine.hpp"
#include <fmod_errors.h>
#include <iostream>

AudioEngine::AudioEngine() : sounds(), loopsPlaying(), soundBanks(),
eventDescriptions(), eventInstances() {}

bool AudioEngine::init() {
    ERRCHECK(FMOD::Studio::System::create(&studioSystem));

    ERRCHECK(studioSystem->initialize(MAX_AUDIO_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

    std::cout <<" Audio Engine: Initialize!";
    return true;
}

void AudioEngine::deactivate() {
    lowLevelSystem->close();
    studioSystem->release();
}

void AudioEngine::update() {
    ERRCHECK(studioSystem->update()); // also updates the low level system
    
}


void AudioEngine::loadFMODStudioBank(const char* filepath) {
    std::cout << "Audio Engine: Loading FMOD Studio Sound Bank " << filepath << '\n';
    FMOD::Studio::Bank* bank = NULL;
    ERRCHECK(studioSystem->loadBankFile(filepath, FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));
    soundBanks.insert({ filepath, bank });
}

void AudioEngine::loadFMODStudioEvent(const char* eventName, std::vector<std::pair<const char*, float>> paramsValues) {
    std::cout << "AudioEngine: Loading FMOD Studio Event " << eventName << '\n';

    // 1. Get the event description
    FMOD::Studio::EventDescription* eventDescription = nullptr;
    ERRCHECK(studioSystem->getEvent(eventName, &eventDescription));

    // 2. Check if the event is valid
    bool isOneShot = false;
    ERRCHECK(eventDescription->isOneshot(&isOneShot));
    std::cout << eventName << " is " << (isOneShot ? "" : "not ") << "a one-shot event\n";

    // 3. Create an instance of the event
    FMOD::Studio::EventInstance* eventInstance = nullptr;
    ERRCHECK(eventDescription->createInstance(&eventInstance));

    // 4. Set any parameters
    for (const auto& parVal : paramsValues) {
        std::cout << "Setting parameter: " << parVal.first << " = " << parVal.second << '\n';
        ERRCHECK(eventInstance->setParameterByName(parVal.first, parVal.second));
    }

    // 5. Store in maps
    eventDescriptions[eventName] = eventDescription;
    eventInstances[eventName] = eventInstance;

    // 6. (Optional) Start playback immediately
    FMOD_STUDIO_PLAYBACK_STATE state;
    ERRCHECK(eventInstance->getPlaybackState(&state));
    std::cout << "Before start(), playback state = ";
    switch (state) {
        case FMOD_STUDIO_PLAYBACK_PLAYING:    std::cout << "PLAYING"; break;
        case FMOD_STUDIO_PLAYBACK_SUSTAINING: std::cout << "SUSTAINING"; break;
        case FMOD_STUDIO_PLAYBACK_STOPPING:   std::cout << "STOPPING"; break;
        case FMOD_STUDIO_PLAYBACK_STOPPED:    std::cout << "STOPPED"; break;
        case FMOD_STUDIO_PLAYBACK_STARTING:   std::cout << "STARTING"; break;
        default:                              std::cout << "UNKNOWN"; break;
    }
    std::cout << std::endl;

    /*ERRCHECK(eventInstance->start());*/

    ERRCHECK(eventInstance->getPlaybackState(&state));
    std::cout << "After start(), playback state = ";
    switch (state) {
        case FMOD_STUDIO_PLAYBACK_PLAYING:    std::cout << "PLAYING"; break;
        case FMOD_STUDIO_PLAYBACK_SUSTAINING: std::cout << "SUSTAINING"; break;
        case FMOD_STUDIO_PLAYBACK_STOPPING:   std::cout << "STOPPING"; break;
        case FMOD_STUDIO_PLAYBACK_STOPPED:    std::cout << "STOPPED"; break;
        case FMOD_STUDIO_PLAYBACK_STARTING:   std::cout << "STARTING"; break;
        default:                              std::cout << "UNKNOWN"; break;
    }
    std::cout << std::endl;
}



void AudioEngine::setFMODEventParamValue(const char* eventName, const char* parameterName, float value) {
    if (eventInstances.count(eventName) > 0)
        ERRCHECK(eventInstances[eventName]->setParameterByName(parameterName, value));
    else
        std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, can't set param \n";

}

void AudioEngine::playEvent(const char* eventName, int instanceIndex) {
    // printEventInfo(eventDescriptions[eventName]);
    auto eventInstance = eventInstances[eventName];
    if (eventInstances.count(eventName) > 0)
        ERRCHECK(eventInstances[eventName]->start());
    else
        std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, cannot play \n";
}

void AudioEngine::stopEvent(const char* eventName, int instanceIndex) {
    if (eventInstances.count(eventName) > 0)
        ERRCHECK(eventInstances[eventName]->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
    else
        std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, cannot stop \n";
}

void AudioEngine::setEventVolume(const char* eventName, float volume0to1) {
    std::cout << "AudioEngine: Setting Event Volume\n";
    ERRCHECK(eventInstances[eventName]->setVolume(volume0to1));
}

bool AudioEngine::eventIsPlaying(const char* eventName, int instance /*= 0*/) {
    FMOD_STUDIO_PLAYBACK_STATE playbackState;
    ERRCHECK(eventInstances[eventName]->getPlaybackState(&playbackState));
    return playbackState == FMOD_STUDIO_PLAYBACK_PLAYING;
}


void AudioEngine::muteAllSounds() {
    ERRCHECK(mastergroup->setMute(true));
    muted = true;
}

void AudioEngine::unmuteAllSound() {
    ERRCHECK(mastergroup->setMute(false));
    muted = false;
}

bool AudioEngine::isMuted() {
    return muted;
}



void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line) {
    if (result != FMOD_OK)
        std::cout << "FMOD ERROR: AudioEngine.cpp [Line " << line << "] " << result << "  - " << FMOD_ErrorString(result) << '\n';
}

void AudioEngine::printEventInfo(FMOD::Studio::EventDescription* eventDescription) {

    int params;
    bool is3D, isOneshot;
    ERRCHECK(eventDescription->getParameterDescriptionCount(&params));
    ERRCHECK(eventDescription->is3D(&is3D));
    ERRCHECK(eventDescription->isOneshot(&isOneshot));

    std::cout << "FMOD EventDescription has " << params << " parameter descriptions, "
        << (is3D ? " is " : " isn't ") << " 3D, "
        << (isOneshot ? " is " : " isn't ") << " oneshot, "
        << (eventDescription->isValid() ? " is " : " isn't ") << " valid."
        << '\n';
}