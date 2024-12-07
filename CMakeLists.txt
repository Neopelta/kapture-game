cmake_minimum_required(VERSION 3.30)
project(kapture)

set(CMAKE_CXX_STANDARD 17)

add_executable(kapture main.cpp
        src/unites/unite.cpp
        include/unitObstacle.h include/units/unite.h
        include/units/eclaireur.h
        include/units/chairACanon.h
        src/unites/chairACanon.cpp
        include/units/troupeDeChoc.h
        src/unites/troupeDeChoc.cpp
        src/unites/eclaireur.cpp
        include/obstacles/obstacle.h
        src/obstacles/obstacle.cpp
        src/obstacles/terrainNu.cpp
        include/obstacles/terrainNu.h
        include/obstacles/foret.h
        src/obstacles/foret.cpp
        include/obstacles/riviere.h
        src/obstacles/riviere.cpp
        include/game/drapeau.h
        src/game/drapeau.cpp
        include/game/cellule.h
        src/game/cellule.cpp
        include/game/joueur.h
        src/game/joueur.cpp
        include/game/plateau.h
        include/game/kaptureGame.h
)
