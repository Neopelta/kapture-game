cmake_minimum_required(VERSION 3.30)
project(kapture)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILES
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
        src/unitObstacle.cpp
        include/commands/command.h
        include/commands/stop.h
        include/commands/MoveCommand.h
        include/game/TurnManager.h
        src/commands/command.cpp
        include/commands/EndTurnCommand.h
        src/commands/EndTurnCommand.cpp
        src/commands/MoveCommand.cpp
        src/commands/stop.cpp
        src/uniteObstacleFactory.cpp
        include/uniteObstacleFactory.h
)

add_library(kapture_lib ${SRC_FILES})


add_executable(kapture main.cpp)
target_link_libraries(kapture PRIVATE kapture_lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(kapture_tests
        test/kaptureGameTest.cpp
        test/kaptureGameTest.h
        test/fightTest.cpp
        test/fightTest.h
)

target_link_libraries(kapture_tests PRIVATE kapture_lib gtest_main gtest)
add_test(NAME KaptureTests COMMAND kapture_tests)
