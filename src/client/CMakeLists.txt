file(GLOB_RECURSE CLIENT_SRC *.cpp)

add_executable(client ${CLIENT_SRC})

target_include_directories(client PRIVATE
    ${CMAKE_SOURCE_DIR}/include/client
    ${CMAKE_SOURCE_DIR}/include/shared
    ${CMAKE_SOURCE_DIR}/dependencies/glm
    ${CMAKE_SOURCE_DIR}/dependencies/json
    ${CMAKE_SOURCE_DIR}/dependencies/stb
    ${CMAKE_SOURCE_DIR}/dependencies/fmod/include
)

target_link_directories(client PRIVATE ${FMOD_LIB_DIR})

target_link_libraries(client PRIVATE
    assimp
    Boost::asio
    Boost::system
    glad
    glfw
    ${FMOD_LIBS}
)

if(WIN32)
    target_link_libraries(client PRIVATE opengl32)
elseif(APPLE)
    target_link_libraries(client PRIVATE "-framework OpenGL")
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(client PRIVATE OpenGL::GL)
endif()

if(WIN32)
    add_custom_command(TARGET client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${FMOD_LIB_DIR}/fmod.dll
            ${FMOD_LIB_DIR}/fmodstudio.dll
            $<TARGET_FILE_DIR:client>
    )
endif()
