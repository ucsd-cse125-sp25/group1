cmake_minimum_required(VERSION 3.14)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "
    Please don't run CMake in the source folder.

    Delete 'CMakeCache.txt' if it was created,
    then run CMake in a separate 'build' folder.

    If you're in the build folder and still see this,
    delete any 'CMakeCache.txt' files outside the build folder.
    ")
endif()

project(GameProject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

if (APPLE)
    set(FMOD_PLATFORM "mac")
    set(FMOD_LIBS fmod fmodstudio)
elseif (WIN32)
    set(FMOD_PLATFORM "windows")
    set(FMOD_LIBS fmod_vc fmodstudio_vc)
elseif (UNIX)
    set(FMOD_PLATFORM "linux")
    set(FMOD_LIBS fmod fmodstudio)
endif()

set(FMOD_ROOT ${CMAKE_SOURCE_DIR}/dependencies/fmod)
set(FMOD_LIB_DIR ${FMOD_ROOT}/${FMOD_PLATFORM}/lib)

add_subdirectory(dependencies/assimp)
add_subdirectory(dependencies/boost)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)

add_subdirectory(src/client)
add_subdirectory(src/server)
