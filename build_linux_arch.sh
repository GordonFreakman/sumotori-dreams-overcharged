#!/bin/bash
set -e

# 1. Arch linux need "venv", if exists - skip.
if [ ! -d "venv" ]; then
    echo "=== First launch. Installing Jinja2 in venv. ==="
    python -m venv venv
    source venv/bin/activate
    pip install --upgrade pip
    pip install jinja2
else
    source venv/bin/activate
fi

# 2. If no "build-portable" exists - cmake cmd.
if [ ! -d "build-portable" ]; then
    cmake -S . -B build-portable -DSUMO_SDL_VERSION=3
fi

cmake --build build-portable
