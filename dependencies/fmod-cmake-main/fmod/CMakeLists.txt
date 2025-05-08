include(fmod_find)

# Ensure FMOD version was set
if (NOT FMOD_VERSION)
    message(WARNING "FMOD_VERSION was not specified, add_library ignored.")
    return()
endif()

# Find platform folder
if (NOT FMOD_PLATFORM)
    fmod_detect_platform(FMOD_PLATFORM)
    message("fmod-cmake: detected platform \"${FMOD_PLATFORM}\"")
endif()

# Find libraries
fmod_find_libs(${FMOD_PLATFORM} ${FMOD_VERSION} FMOD_LIBS FMOD_STUDIO_LIBS FMOD_DLLS)
set(FMOD_DLLS ${FMOD_DLLS} CACHE STRING "" FORCE) # cache these for use with `fmod_copy_libs`
set(FMOD_LIBS ${FMOD_LIBS} CACHE STRING "" FORCE)
set(FMOD_STUDIO_LIBS ${FMOD_LIBS} CACHE STRING "" FORCE)
set(FMOD_INCLUDE_DIR ${FMOD_VERSION}/include)

# Create the library interfaces
add_library(fmod INTERFACE)
target_link_libraries(fmod INTERFACE ${FMOD_LIBS})
target_include_directories(fmod INTERFACE ${FMOD_INCLUDE_DIR})

add_library(fmodstudio INTERFACE)
target_link_libraries(fmodstudio INTERFACE ${FMOD_STUDIO_LIBS})
target_include_directories(fmodstudio INTERFACE ${FMOD_INCLUDE_DIR})

# Platform-specific linkage
if (EMSCRIPTEN)
    target_link_options(fmod INTERFACE
        -sEXPORTED_RUNTIME_METHODS=['cwrap','setValue','getValue'])
    target_link_options(fmodstudio INTERFACE
        -sEXPORTED_RUNTIME_METHODS=['cwrap','setValue','getValue'])
else()
    # add fmod dependency on non-emscripten platforms since it emscripten includes it automatically
    target_link_libraries(fmodstudio INTERFACE fmod)
endif()
