#!/bin/bash

# chmod +x build.sh

if [ ! -d "build" ] || [ ! -f "build/CMakeCache.txt" ]; then
    if ! command -v cmake &> /dev/null; then
        echo "Error: CMake n'est pas installé. Version minimum requise: 3.30"
        echo "Veuillez installer CMake avant de continuer."
        exit 1
    fi

    if ! command -v make &> /dev/null; then
        echo "Error: Make n'est pas installé."
        echo "Veuillez installer build-essential avant de continuer."
        exit 1
    fi

    mkdir -p build
    cd build
    cmake ..
else
    cd build
fi

if make; then
    ./kapture
else
    echo "Erreur lors de la compilation"
    exit 1
fi