#!/bin/bash

: << 'DOC'
Instructions pour utiliser GDB :

# Commandes de base GDB :
break main                    # Place un point d'arrêt sur main
run                          # Lance le programme
next (ou n)                  # Exécute la ligne suivante
step (ou s)                  # Entre dans la fonction
continue (ou c)              # Continue jusqu'au prochain point d'arrêt
print variable               # Affiche la valeur d'une variable
backtrace (ou bt)           # Affiche la pile d'appels
quit (ou q)                 # Quitte GDB

# Pour déboguer spécifiquement le jeu :
break TurnManager::executeMove     # Point d'arrêt sur la fonction de déplacement
break unite::setPosition          # Point d'arrêt sur le changement de position
print currentX                    # Voir la position X actuelle
print currentY                    # Voir la position Y actuelle
print *unit                      # Voir les détails de l'unité

# Pour suivre les déplacements :
display currentX                  # Affiche automatiquement X à chaque arrêt
display currentY                  # Affiche automatiquement Y à chaque arrêt
DOC

# Vérifie si cmake est installé
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake n'est pas installé."
    exit 1
fi

# Vérifie si gdb est installé
if ! command -v gdb &> /dev/null; then
    echo "Error: GDB n'est pas installé. Installez-le avec : sudo apt-get install gdb"
    exit 1
fi

# Crée et configure le build en mode Debug
echo "Configuration du build en mode Debug..."
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Compile le projet
echo "Compilation du projet..."
make -j

# Vérifie si la compilation a réussi
if [ $? -ne 0 ]; then
    echo "Erreur lors de la compilation"
    exit 1
fi

# Lance GDB
echo "Lancement de GDB..."
gdb --quiet ./kapture