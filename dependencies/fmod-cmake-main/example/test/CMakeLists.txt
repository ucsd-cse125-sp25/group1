project(fmod_cmake_test)

set (CMAKE_CXX_STANDARD 11)

add_executable(fmod_cmake_test fmod_cmake_test.cpp)
target_link_libraries(fmod_cmake_test PRIVATE fmod)

# On Windows, copy all DLLs associated with the exe to the output directory
if (WIN32)
    add_custom_command(TARGET fmod_cmake_test PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:fmod_cmake_test> $<TARGET_FILE_DIR:fmod_cmake_test>
    )
    fmod_copy_dlls()
endif()

if (EMSCRIPTEN)
    set_target_properties(fmod_cmake_test PROPERTIES
        SUFFIX .html
    )
    target_link_options(fmod_cmake_test PRIVATE
        -sUSE_SDL=2
        --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/../assets@assets
    )
    target_compile_options(fmod_cmake_test PRIVATE -sUSE_SDL=2)
else()

    # Make a symlink to the assets folder in the output directory
    if (NOT EXISTS ${CURRENT_BINARY_DIR}/assets)
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${FMOD_CMAKE_ROOT}/example/assets
            ${CMAKE_CURRENT_BINARY_DIR}/assets)
    endif()

    find_library(SDL2 SDL2)
    if (NOT SDL2)
        # Fetch and link to SDL2
        include(FetchContent)

        FetchContent_Declare(SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG        fb1497566c5a05e2babdcf45ef0ab5c7cca2c4ae
        )

        FetchContent_MakeAvailable(SDL2)
    endif()

    target_link_libraries(fmod_cmake_test PRIVATE SDL2::SDL2 SDL2::SDL2main)
endif()
