file(GLOB_RECURSE CLIENT_SRC *.cpp)

add_executable(client ${CLIENT_SRC})

target_include_directories(client PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/dependencies/json
    ${CMAKE_SOURCE_DIR}/dependencies/glm
)

target_link_libraries(client PRIVATE
    assimp
    Boost::asio
    Boost::system
    glad
    glfw
)

if(WIN32)
    target_link_libraries(client PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(client PRIVATE "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(client PRIVATE OpenGL::GL)
endif()
