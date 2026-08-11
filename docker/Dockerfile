FROM debian:bookworm

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
      build-essential \
      ca-certificates \
      cmake \
      file \
      git \
      ninja-build \
      python3 \
      python3-jinja2 \
      binutils \
      g++-mingw-w64-x86-64 \
      gcc-mingw-w64-x86-64 \
      pkg-config \
      libasound2-dev \
      libdbus-1-dev \
      libdrm-dev \
      libegl1-mesa-dev \
      libgbm-dev \
      libgl1-mesa-dev \
      libgles2-mesa-dev \
      libpulse-dev \
      libudev-dev \
      libwayland-dev \
      libx11-dev \
      libxcursor-dev \
      libxext-dev \
      libxfixes-dev \
      libxi-dev \
      libxkbcommon-dev \
      libxrandr-dev \
      libxss-dev \
      libxtst-dev \
      wayland-protocols \
    && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --set x86_64-w64-mingw32-gcc /usr/bin/x86_64-w64-mingw32-gcc-posix \
 && update-alternatives --set x86_64-w64-mingw32-g++ /usr/bin/x86_64-w64-mingw32-g++-posix

WORKDIR /src
