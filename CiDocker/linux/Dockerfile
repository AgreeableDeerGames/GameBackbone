FROM ubuntu:18.04

RUN apt-get update && apt-get install -y build-essential \
    sudo \
    cmake \
    valgrind \ 
    libboost-all-dev \
    ninja-build \
    wget \
    git \
    libpthread-stubs0-dev \
    libgl1-mesa-dev \
    libx11-dev \
    libxrandr-dev \
    libfreetype6-dev \
    libglew1.5-dev \
    libjpeg8-dev \
    libsndfile1-dev \
    libopenal-dev \
    libudev-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN mkdir build_sfml && \
    cd build_sfml && \
    git clone --single-branch --branch 2.5.x https://github.com/SFML/SFML.git && \
    mkdir build && \
    cd build && \
    cmake ../SFML && \
    make && \
    make install && \
    cd .. && \
    cd ..

run mkdir build_tgui && \
    cd build_tgui && \
    git clone --single-branch --branch 0.8 https://github.com/texus/TGUI.git && \
    mkdir build && \
    cd build && \
    cmake ../TGUI && \
    make && \
    make install && \
    cd .. && \
    cd .. 
