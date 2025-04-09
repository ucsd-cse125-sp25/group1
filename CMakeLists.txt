cmake_minimum_required(VERSION 3.14)

project(GameProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

if(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

include_directories(${CMAKE_SOURCE_DIR}/GameProject/include)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/GameProject/src/*.cpp)
add_executable(GameProject ${SRC_FILES})

find_package(glfw3 QUIET)

if(NOT glfw3_FOUND)
    message(STATUS "Downloading GLFW...")

    include(FetchContent)

    FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.3.10
    )

    FetchContent_MakeAvailable(glfw)
endif()

target_link_libraries(GameProject PRIVATE glfw)

if(WIN32)
    target_link_libraries(GameProject opengl32)
elseif(APPLE)
    target_link_libraries(GameProject PRIVATE glfw "-framework OpenGL")
endif()
