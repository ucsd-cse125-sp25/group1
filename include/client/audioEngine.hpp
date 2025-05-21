#pragma once
///
/// @file AudioEngine.h
/// 
/// FMOD wrapper which loads sound files (.wav, .mp3, .ogg etc) and FMOD soundbanks (.bank files)
/// and supports looping or one-shot playback in stereo, as well as customizable 3D positional audio
/// Implements the FMOD Studio and FMOD Core API's to allow audio file-based implementations,
/// alongside/in addition to use of FMOD Studio Sound Banks.
///
/// @author Ross Hoyt
/// @dependencies FMOD Studio & Core
/// 
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
//#include "SoundInfo.h"

/**
 * Error Handling Function for FMOD Errors
 * @param result - the FMOD_RESULT generated during every FMOD 
 */
void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line);
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

/**
 * Class that handles the process of loading and playing sounds by wrapping FMOD's functionality.
 * Deals with all FMOD calls so that FMOD-specific code does not need to be used outside this class.
 * Only one AudioEngine should be constructed for an application.
 */
class AudioEngine {
public:
    /**
     * Default AudioEngine constructor. 
     * AudioEngine::init() must be called before using the Audio Engine 
     */
    AudioEngine();

    /**
     * Initializes Audio Engine Studio and Core systems to default values. 
     */
    bool init();

    /**
     * Method that is called to deactivate the audio engine after use.
     */
    void deactivate();

    /**
    * Method which should be called every frame of the game loop
    */
    void update();

    /**
     * Loads an FMOD Studio soundbank 
     * TODO Fix
     */
    void loadFMODStudioBank(const char* filePath);
    
    /**
     * Loads an FMOD Studio Event. The Soundbank that this event is in must have been loaded before
     * calling this method.
     * TODO Fix
     */
    void loadFMODStudioEvent(const char* eventName, std::vector<std::pair<const char*, float>> paramsValues = { });
    
    /**
     * Sets the parameter of an FMOD Soundbank Event Instance.
     */
    void setFMODEventParamValue(const char* eventName, const char* parameterName, float value);
    
    /**
     * Plays the specified instance of an event
     * TODO support playback of multiple event instances
     * TODO Fix playback
     */
    void playEvent(const char* eventName, int instanceIndex = 0);
    
    /**
     * Stops the specified instance of an event, if it is playing.
     */
    void stopEvent(const char* eventName, int instanceIndex = 0);
 
    /**
     * Sets the volume of an event.
     * @param volume0to1 - volume of the event, from 0 (min vol) to 1 (max vol)
     */
    void setEventVolume(const char* eventName, float volume0to1 = .75f);

    /**
     * Checks if an event is playing.
     */
    bool eventIsPlaying(const char* eventName, int instance = 0);

    /**
     * Mutes all sounds for the audio engine
     */
	void muteAllSounds();

    /**
     * Unmutes all sounds for the audio engine
     */
	void unmuteAllSound();

    /**
     * Returns true if the audio engine is muted, false if not
     */
	bool isMuted();

    // The audio sampling rate of the audio engine
    static const int AUDIO_SAMPLE_RATE = 44100;

private:  

    /**
     * Initializes the reverb effect
     */
    void initReverb();

    /**
     * Prints debug info about an FMOD event description
     */
    void printEventInfo(FMOD::Studio::EventDescription* eventDescription);

    // FMOD Studio API system, which can play FMOD sound banks (*.bank)
    FMOD::Studio::System* studioSystem = nullptr;       
    
    // FMOD's low-level audio system which plays audio files and is obtained from Studio System
    FMOD::System* lowLevelSystem = nullptr;          

    // Max FMOD::Channels for the audio engine 
    static const unsigned int MAX_AUDIO_CHANNELS = 1024; 
    
    // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.
    const float DISTANCEFACTOR = 1.0f;  
 
    // Listener head position, initialized to default value
    FMOD_VECTOR listenerpos = { 0.0f, 0.0f, -1.0f * DISTANCEFACTOR };
    
    // Listener forward vector, initialized to default value
    FMOD_VECTOR forward     = { 0.0f, 0.0f, 1.0f };
    
    // Listener upwards vector, initialized to default value
    FMOD_VECTOR up          = { 0.0f, 1.0f, 0.0f };

    // Main group for low level system which all sounds go though
    FMOD::ChannelGroup* mastergroup = 0;

    // Low-level system reverb TODO add multi-reverb support
	FMOD::Reverb3D* reverb;

	// Reverb origin position
	FMOD_VECTOR revPos = { 0.0f, 0.0f, 0.0f };

	// reverb min, max distances
	float revMinDist = 10.0f, revMaxDist = 50.0f;

    // flag tracking if the Audio Engin is muted
    bool muted = false;

    /*
     * Map which stores the current playback channels of any playing sound loop
     * Key is the SoundInfo's uniqueKey field.
     * Value is the FMOD::Channel* the FMOD::Sound* is playing back on.
     */
    std::map<std::string, FMOD::Channel*> loopsPlaying;

    /*
     * Map which stores the soundbanks loaded with loadFMODStudioBank()
     */
    std::map<std::string, FMOD::Studio::Bank*> soundBanks;
    
    /*
     * Map which stores event descriptions created during loadFMODStudioEvent()
     */
    std::map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;
    
    /*
     * Map which stores event instances created during loadFMODStudioEvent()
     */
    std::map<std::string, FMOD::Studio::EventInstance*> eventInstances;
};