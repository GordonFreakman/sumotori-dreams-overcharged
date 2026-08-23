# Sumotori Dreams: OVERCHARGED

An enhancement mod of Sumotori Dreams to add new features and fix some long-standing bugs.

## Features

- Rewritten renderer, moving most of the implementation from the CPU to the GPU.
- Custom ImGui theme with proper UI scaling.
- New gamemodes. (Boryoku)
- Restoration of the original Breakpoint 2007 build gameplay.
- Expanded engine limits. (Over 4000 boxes instead of only just 512.)
- Stability improvements
- New editor features.
- Improved editor as a whole.

## Build

```sh
cmake -S . -B build-portable -DSUMO_SDL_VERSION=3
cmake --build build-portable
```

CLI: `--fullscreen` / `--windowed`, `--width` / `--height`,
`--audio sdl|miniaudio`, `--skip-launcher`, `--editor`, `--mod <file.smo>`.

