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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

if(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/GameProject/include)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/GameProject/src/*.cpp)
add_executable(GameProject ${SRC_FILES})

add_subdirectory(dependencies/glfw)
target_link_libraries(GameProject PRIVATE glfw)

add_subdirectory(dependencies/glad)
target_link_libraries(GameProject PRIVATE glad)

if(WIN32)
    target_link_libraries(GameProject PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(GameProject PRIVATE "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(GameProject PRIVATE OpenGL::GL)
endif()
