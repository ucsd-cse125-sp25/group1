file(GLOB_RECURSE SERVER_SRC *.cpp)

add_executable(server ${SERVER_SRC})

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/include/server
    ${CMAKE_SOURCE_DIR}/include/shared
    ${CMAKE_SOURCE_DIR}/dependencies/glm
    ${CMAKE_SOURCE_DIR}/dependencies/json
    ${CMAKE_SOURCE_DIR}/dependencies/fmod-cmake-main
)

target_link_libraries(server PRIVATE
    Boost::asio
    Boost::system
    fmod
    fmodstudio
    fsbank
)
