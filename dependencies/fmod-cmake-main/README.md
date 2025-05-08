# FMOD CMake

A CMake interface for linking to FMOD Studio and Core APIs on multiple platforms for C/C++ projects.
The way it works is by downloading the FMOD libs and headers from fmod.com and copying them into your project.

This interface has been tested and working on
- MacOS arm64
- Linux Ubuntu aarch64
- Windows arm64
- Emscripten WASM

## How to use

### 1. Clone this project as a submodule in your repository

### 2. Get FMOD

- Download the FMOD API platforms and version you need from fmod.com
- Extract and install the files

*Note:* You will need an FMOD account to access the downloads page. If you are planning on using FMOD commercially, you will need to follow their licensing structure and terms.

### 3. Copy the FMOD headers

Find the C/C++ header files in one of your download folders or installations, usually located at `<fmod-api-root>/api/core/inc` and `<fmod-api-root>/api/studio/inc` for both Core and Studio APIs, respectively.

Copy all `.h` and `.hpp` from here into this repository's `<this-repo>/fmod/<version>/include` folder. Any other file types like `.cs` are not necessary.
For the path to copy the files, let's say your version of FMOD is `2.02.21` - the headers should then go into `<this-repo>/fmod/2.02.21/include`.

*Note:* by specifying version folders, switching between multiple versions is supported by changing the `FMOD_VERSION` cmake variable as seen in step 5.

### 4. Copy the FMOD libraries for each platform

#### Mac OS AppleClang (x86_64, arm64)

Library file locations (from download)
- Core:   `api/core/lib`
    - libfmod.dylib
    - libfmodL.dylib

- Studio: `api/studio/lib`
    - libfmodstudio.dylib
    - libfmodstudioL.dylib

Destination folder (in this repo):
    `fmod/<version>/lib/macos`
e.g. with FMOD v2.02.21, it would be `fmod/2.02.21/lib/macos`


#### Linux (x86, x86_64, arm, arm64)

Library file locations (from download)
- Core:   `api/core/lib/<arch>`
    - libfmod.so.\*.\*
    - libfmod.so (symlink)
    - libfmodL.so.\*.\*
    - libfmodL.so (symlink)

- Studio: `api/studio/lib/<arch>`
    - libfmodstudio.so.\*.\*
    - libfmodstudio.so (symlink)
    - libfmodstudioL.so.\*.\*
    - libfmodstudioL.so (symlink)

Destination folder (in this repo):
    `fmod/<version>/lib/linux-<arch>`

*Platform note:*
Please make sure to include the symlinks with the plain `.so` extension in addition to the actual lib files.

#### Windows MSVC (x86, x64, arm64)

Library file locations (from download)
- Core:   `api/core/lib/<arch>`
    - fmod_vc.lib
    - fmodL_vc.lib
    - fmod.dll
    - fmodL.dll

- Studio: `api/studio/lib/<arch>`
    - fmodstudio_vc.lib
    - fmodstudioL_vc.lib
    - fmodstudio.dll
    - fmodstudioL.dll

Destination folder (in this repo):
    `fmod/<version>/lib/windows-<arch>`
e.g. on x64 FMOD v2.02.21, it would be `fmod/2.02.21/lib/windows-x64`

*Platform note:*
The dll files are optional to include in the repo folder. If you do include it, you can call `fmod_copy_libs(TARGET_NAME)` inside the CMakeLists file containing your `add_executable` declaration, and it will automatically copy the dlls to the same directory as your built binary. Otherwise, you may omit these files from this repo, and drop them into the binary directory manually.

#### HTML5

Library file locations (from download)
- Core:   `api/core/lib/upstream/w32`
    - fmod_wasm.a
    - fmodL_wasm.a
    - fmod_reduced_wasm.a

- Studio: `api/studio/lib/upstream/w32`
    - fmodstudio_wasm.a
    - fmodstudioL_wasm.a

Destination folder (in this repo):
    `fmod/<version>/lib/html5-w32`

*Platform notes:*
- The easiest and most reliable way to set up Emscripten builds in CMake is by passing the toolchain file to the CMake command line. e.g. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path/to/Emscripten.cmake>`
- Assuming you've already installed emsdk and the latest version of Emscripten, this file is usually located at `<emsdk-root>/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake`
- In order to use the reduced fmod libs, you must set `FMOD_HTML5_REDUCED` to a truthy value in the CMakeLists file. When falsy, the fmodstudio logging library is linked to, even in non-debug builds, as the non-logging library contains the reduced fmod core version inside of it.

#### More platforms to come...

*Note:* You only need to provide what you want to support building for.

For example, if you only need to link FMOD Core, you don't need to copy any of the FMOD Studio headers or libraries; or if you only need to build for Windows x86_64, then there's no need to add Windows arm64 files, etc.

### 5. Consume the FMOD CMake Interface

In your `CMakeLists.txt` file, add this repository submodule as a subdirectory, specifying `FMOD_VERSION`. The version you set should directly correlate with the subfolder name.

For example, for libraries inside of `fmod/2.02.21`, use:

```cmake
set(FMOD_VERSION 2.02.21 CACHE STRING "" FORCE)
add_subdirectory(lib/fmod-cmake)
```

Add link target `fmod` for FMOD Core, and `fmodstudio` for FMOD Studio
```cmake
add_executable(my_exe main.cpp)
target_link_libraries(my_exe PRIVATE fmod)
```

*Notes:*
- You may bypass auto-platform-detection by explicitly setting the platform lib sub-folder via `set(FMOD_PLATFORM "macos" CACHE STRING "" FORCE)`
- For HTML5 builds, if you set `FMOD_HTML5_REDUCED` to `ON` the interface will search for `fmod_reduced_wasm.a`, and `fmodstudio_wasm.a`, which both contain reduced features. Please check the HTML5-specific platform information in the FMOD docs for more info. `fmodstudioL_wasm.a` is the only non-reduced studio build, so this is the file the interface will search for when `FMOD_HTML5_REDUCED` is falsy.
- If on Windows, to auto-copy .dll files to your exe's binary directory, call `fmod_copy_dlls()` after your `add_executable` declaration.

## Contributing

Please submit an issue for suggestions, requests or bug reports. Pull requests are welcome, especially for the following:

- Support for other platforms (Mobile, Consoles, etc.)
- Added robustness to CMake files fixing bugs and covering edge cases, etc.
- CMake compilation tests, library and header location checks, provide better error messages

## FMOD Licensing Note

Since FMOD is proprietary, distribution is limited to downloads directly from their website.
Therefore, please refrain from committing any of the FMOD libs and headers into any public repository.
Also, if using FMOD commercially, you will need to obtain a license from them.
