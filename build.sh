#!/bin/bash

# Si le dossier build n'existe pas ou ne contient pas de CMakeCache.txt
if [ ! -d "build" ] || [ ! -f "build/CMakeCache.txt" ]; then
    # Vérifie les prérequis
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

    # Configuration initiale
    mkdir -p build
    cd build
    cmake ..
else
    # Si build existe déjà, on y va directement
    cd build
fi

# Compile et exécute
if make; then
    ./kapture
else
    echo "Erreur lors de la compilation"
    exit 1
fi