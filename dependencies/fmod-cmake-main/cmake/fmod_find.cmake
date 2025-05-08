# Get the iOS platform. Please only call this when IOS is set to TRUE, otherwise a cmake error will be emitted
# @param _PLATFORM  [out] name of variable to receive iOS sub-platform (STRING)
# @param _SIMULATOR [out] name of variable to receive whether the platform is a simulator (BOOL)
macro(fmod_detect_ios_platform _PLATFORM _SIMULATOR)
    if (NOT IOS) # just in case someone tries to call this without being ios
        message(FATAL_ERROR "fmod-cmake: cannot call fmod_detect_ios_platform when not an iOS platform")
    endif()

    string(TOUPPER "${CMAKE_OSX_SYSROOT}" IOS_SYSROOT)
    if (IOS_SYSROOT MATCHES "PLATFORMS/APPLETV")
        set(${_PLATFORM} appletvos)
    elseif(IOS_SYSROOT MATCHES "PLATFORMS/IPHONE")
        set(${_PLATFORM} iphone)
    elseif(IOS_SYSROOT MATCHES "PLATFORMS/XR")
        set(${_PLATFORM} xr)
    else()
        message(FATAL_ERROR "fmod-cmake: iOS platform at sysroot ${CMAKE_OSX_SYSROOT} is unsupported and/or unrecognized")
    endif()

    # Check if simulator
    if (IOS_SYSROOT MATCHES "SIMULATOR.PLATFORM")
        set(${_SIMULATOR} TRUE)
    else()
        set(${_SIMULATOR} FALSE)
    endif()
endmacro()

# Get the Android platform. Please only call this when ANDROID is set to TRUE, otherwise a cmake error will be emitted
# @param _ARCH  [out] name of variable to receive Android arch (STRING)
macro(fmod_detect_android_arch _ARCH)
    if (NOT ANDROID)
        message(FATAL_ERROR "fmod-cmake: cannot call fmod_detect_android_ARCH when not an Android platform")
    endif()

    string(TOUPPER "${CMAKE_ANDROID_ARCH_ABI}" ANDROID_ARCH)
    if (ANDROID_ARCH STREQUAL "ARM64-V8A")
        set(${_ARCH} "arm64-v8a")
    elseif(ANDROID_ARCH STREQUAL "ARMEABI-V7A")
        set(${_ARCH} "armeabi-v7a")
    elseif(ANDROID_ARCH STREQUAL "X86")
        set(${_ARCH} "x86")
    elseif(ANDROID_ARCH STREQUAL "X86_64")
        set(${_ARCH} "x86_64")
    else()
        message(FATAL_ERROR "fmod-cmake: Android platform ${CMAKE_ANDROID_ARCH_ABI} is unsupported and/or unrecognized")
    endif()
endmacro()

# Sets detected platform folder name into a provided var name.
# Emits a warning if current platform has not been tested yet.
# Emits an error if platform is unsupported by us or not provided by FMOD.
# @param PLATFORM_VAR [out] name of the variable to receive the detected platform name.
macro(fmod_detect_platform PLATFORM_VAR)
    # FIXME: this regex can be simplified a lot, it's 'just adapted from a StackOverflow post that "works"
    set(X86_64_REGEX "(x86)|(X86)|(amd64)|(AMD64)|(x86_64)|(X86_64)|(x64)|(X64)")

	if (IOS)
        message(WARNING "fmod-cmake: iOS platform has not been tested yet")
		set(${PLATFORM_VAR} "ios")
	elseif(APPLE)
		set(${PLATFORM_VAR} "macos")
	elseif(WIN32)
		if (NOT MSVC) # FMOD only provides MSVC builds across all archs
            message(FATAL_ERROR "Non-MSVC Windows compilers not supported")
        endif()

        if (CMAKE_SYSTEM_PROCESSOR MATCHES ${X86_64_REGEX})
            if (CMAKE_SIZEOF_VOID_P EQUAL 4)
                set (${PLATFORM_VAR} windows-x86)
            else()
                set (${PLATFORM_VAR} windows-amd64)
            endif()
        elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm)|(ARM)" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
            set (${PLATFORM_VAR} windows-arm64)
        else()
            message(FATAL_ERROR "fmod-cmake: Windows with architecture ${CMAKE_SYSTEM_PROCESSOR} is not supported")
        endif()
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")

        if (CMAKE_SYSTEM_PROCESSOR MATCHES ${X86_64_REGEX})
            if (CMAKE_SIZEOF_VOID_P EQUAL 4)
                set (${PLATFORM_VAR} linux-x86)
            else()
                set (${PLATFORM_VAR} linux-x86_64)
            endif()

        elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "(ARM)|(arm)|(aarch)|(AARCH)")
            if (CMAKE_SIZEOF_VOID_P EQUAL 4)
                set (${PLATFORM_VAR} linux-arm)
            else()
                set (${PLATFORM_VAR} linux-arm64)
            endif()
        else()
            message(FATAL_ERROR
                "Linux with architecture ${CMAKE_SYSTEM_PROCESSOR} is not supported")
        endif()

    elseif(ANDROID)
        message(WARNING "fmod-cmake: Android platform has not been tested yet")
        fmod_detect_android_arch(ANDROID_ARCH)
        set(${PLATFORM_VAR} android-${ANDROID_ARCH})
    elseif(EMSCRIPTEN)
        set (${PLATFORM_VAR} html5-w32)
    endif()
endmacro()

# Find the FMOD libraries by platform and version
# @param _PLATFORM_NAME    [in] name of the platform folder
# @param _VERSION          [in] name of the version folder
# @param _FMOD_LIBS        [out] name of the variable to output FMOD Core libraries to
# @param _FMOD_STUDIO_LIBS [out] name of the variable to output FMOD Studio libraries to
# @param _FMOD_DLLS        [out] name of the variable to output FMOD DLLS to (on non-Windows platform, the var will always be set to "")
macro(fmod_find_libs _PLATFORM_NAME _VERSION _FMOD_LIBS _FMOD_STUDIO_LIBS _FMOD_DLLS)
    # Determine that library root directory
    set(FMOD_LIB_ROOT ${FMOD_CMAKE_ROOT}/fmod/${_VERSION}/lib/${_PLATFORM_NAME})

    set(${_FMOD_DLLS} "")

    # On debug builds, link to the FMOD logging libraries
    string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_UPPER)
    if (BUILD_TYPE_UPPER MATCHES "DEBUG" OR BUILD_TYPE_UPPER MATCHES "RELWITHDEBINFO")
        set(FMOD_LIB_TYPE "L") # FMOD logging libraries append an 'L' at the end of the name
    else()
        set(FMOD_LIB_TYPE "")
    endif()

    # Get the library files per platform
    if (IOS)
        fmod_detect_ios_platform(IOS_PLATFORM IOS_SIMULATOR)
        if (IOS_SIMULATOR)
            set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/libfmod${FMOD_LIB_TYPE}_${IOS_PLATFORM}simulator.a)
            set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/libfmodstudio${FMOD_LIB_TYPE}_${IOS_PLATFORM}simulator.a)
        else()
            set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/libfmod${FMOD_LIB_TYPE}_${IOS_PLATFORM}os.a)
            set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/libfmodstudio${FMOD_LIB_TYPE}_${IOS_PLATFORM}os.a)
        endif()
    elseif(APPLE)
        set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/libfmod${FMOD_LIB_TYPE}.dylib)
        set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/libfmodstudio${FMOD_LIB_TYPE}.dylib)
    elseif(WIN32)
        set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/fmod${FMOD_LIB_TYPE}_vc.lib)
        set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/fmodstudio${FMOD_LIB_TYPE}_vc.lib)
        set(${_FMOD_DLLS}                                # set the dlls var, since we're on windows
            ${FMOD_LIB_ROOT}/fmod${FMOD_LIB_TYPE}.dll
            ${FMOD_LIB_ROOT}/fmodstudio${FMOD_LIB_TYPE}.dll
        )
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/libfmod${FMOD_LIB_TYPE}.so)
        set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/libfmodstudio${FMOD_LIB_TYPE}.so)
    elseif(ANDROID)
        set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/fmod${FMOD_LIB_TYPE}.so)
        set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/fmodstudio${FMOD_LIB_TYPE}.so)
    elseif(EMSCRIPTEN)
        if (FMOD_HTML5_REDUCED)
            set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/fmod_reduced_wasm.a)
            set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/fmodstudio_wasm.a)
        else()
            set(${_FMOD_LIBS}        ${FMOD_LIB_ROOT}/fmod${FMOD_LIB_TYPE}_wasm.a)
            set(${_FMOD_STUDIO_LIBS} ${FMOD_LIB_ROOT}/fmodstudioL_wasm.a)
        endif()
    endif()
endmacro()
