# On Windows platform, copies the appropriate DLLs next to the target
# Okay to call on other platforms, but logs a warning
# @param TARGET (optional: default is the current project name)
# @note depends on FMOD_DLL and FMOD_STUDIO_DLL being cached in the fmod/CMakeLists.txt file
macro(fmod_copy_dlls)
    if (NOT WIN32)
            message(WARNING "fmod-cmake: A call to `fmod_copy_dlls` was made on a non-Windows platform")
        return()
    endif()

    # Get the target to copy the dlls next to
    if (${ARGV0})
        set (TARGET ${ARGV0})
    else()
        set (TARGET ${PROJECT_NAME})
    endif()

    # Copy FMOd Core dll if user provided one in the fmod directory
    if (EXISTS ${FMOD_DLL})

        get_target_property(TARGET_DIR ${TARGET} BINARY_DIR)
        get_filename_component(FMOD_DLL_FILENAME ${FMOD_DLL} NAME)

        if (NOT EXISTS ${TARGET_DIR})
            message(WARNING "Could not copy FMOD Core dll: Failed to find target directory for target: ${TARGET}.")
            return()
        endif()

        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${FMOD_DLL}
                ${TARGET_DIR}/${FMOD_DLL_FILENAME}
        )
    endif()

    # Copy FMOD Studio dll if user provided one
    if (EXISTS ${FMOD_STUDIO_DLL})

        get_target_property(TARGET_DIR ${TARGET} BINARY_DIR)

        if (NOT EXISTS ${TARGET_DIR})
            message(WARNING "Could not copy FMOD Studio dll: Failed to find target directory for target: ${TARGET}.")
            return()
        endif()

        get_filename_component(FMOD_STUDIO_DLL_FILENAME ${FMOD_STUDIO_DLL} NAME)

        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${FMOD_DLL}
                ${TARGET_DIR}/${FMOD_STUDIO_DLL_FILENAME}
        )
    endif()

endmacro()

macro(fmod_copy_libs)
    # Get the target to copy the dlls next to
    if (${ARGV0})
        set (TARGET ${ARGV0})
    else()
        set (TARGET ${PROJECT_NAME})
    endif()

    if (WIN32)
        fmod_copy_dlls(${TARGET})
    endif()

    if (EXISTS ${FMOD_LIBS})
        get_target_property(TARGET_DIR ${TARGET} BINARY_DIR)

        if (NOT EXISTS ${TARGET_DIR})
            message(WARNING "Could not copy FMOD Core dll: Failed to find target directory for target: ${TARGET}.")
            return()
        endif()

        foreach(LIB ${FMOD_LIBS})
            get_filename_component(LIB_NAME ${LIB} NAME)
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${LIB}
                    ${TARGET_DIR}/${LIB_NAME}
            )
        endforeach()
    endif()

    if (EXISTS ${FMOD_STUDIO_LIBS})
        get_target_property(TARGET_DIR ${TARGET} BINARY_DIR)

        if (NOT EXISTS ${TARGET_DIR})
            message(WARNING "Could not copy FMOD Core dll: Failed to find target directory for target: ${TARGET}.")
            return()
        endif()

        foreach(LIB ${FMOD_STUDIO_LIBS})
            get_filename_component(LIB_NAME ${LIB} NAME)
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${LIB}
                    ${TARGET_DIR}/${LIB_NAME}
            )
        endforeach()
    endif()

endmacro()