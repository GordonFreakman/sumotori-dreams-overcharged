# Sumotori Dreams

## Requirements

- CMake 
- A compiler with support of both **C17 and C++17**
- Python3 and Jinja2

## Build

```sh
cmake -S . -B build-portable -DSUMO_SDL_VERSION=3
cmake --build build-portable
```

CLI: `--fullscreen` / `--windowed`, `--width` / `--height`,
`--audio sdl|miniaudio`, `--skip-launcher`, `--editor`, `--mod <file.smo>`.

