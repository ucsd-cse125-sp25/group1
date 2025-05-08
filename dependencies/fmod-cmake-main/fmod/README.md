## Folder structure

- \<FMOD_VERSION\>/
    - include/
    - lib/
        - platform1-arch1/
        - platform1-arch2/
        - platform2-arch1/
        - .../

## Example

- 2.02.21/
    - include/
        - fmod_codec.h
        - fmod_common.h
        - fmod_dsp_effects.h
        - ...
    - lib/
        - html5-w32/
            - fmod_wasm.a
            - fmodL_wasm.a
            - fmodstudio_wasm.a
            - fmodstudioL_wasm.a
        - macos/
            - libfmod.dylib
            - libfmodL.dylib
            - libfmodstudio.dylib
            - libfmodstudioL.dylib
        - windows-arm64/
            - fmod_vc.lib
            - fmodL_vc.lib
            - fmodstudio_vc.lib
            - fmodstudioL_vc.lib
            - fmod.dll (optional, see root README.md)
            - fmodL.dll (optional)
            - fmodstudio.dll (optional)
            - fmodstudioL.dll (optional)  
        - windows-x86/ (same as above)
        - windows-x86_64/ (same as above)
        - linux-arm/ (todo, not tested yet)
        - linux-arm64/
        - linux-x86/
        - linux-x86_64/
