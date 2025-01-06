# Définition des variables
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = kapture

# Déclaration des fichiers sources et en-têtes
SRC_FILES = main.cpp \
            src/unites/unite.cpp \
            src/unites/chairACanon.cpp \
            src/unites/eclaireur.cpp \
            src/unites/troupeDeChoc.cpp \
            src/unitObstacle.cpp \
            src/uniteObstacleFactory.cpp \
            src/obstacles/obstacle.cpp \
            src/obstacles/terrainNu.cpp \
            src/obstacles/foret.cpp \
            src/obstacles/riviere.cpp \
            src/game/drapeau.cpp \
            src/game/cellule.cpp \
            src/game/joueur.cpp \
            src/commands/command.cpp \
            src/commands/EndTurnCommand.cpp \
            src/commands/MoveCommand.cpp \
            src/commands/stop.cpp

HEADERS = include/units/unite.h \
          include/units/eclaireur.h \
          include/units/chairACanon.h \
          include/units/troupeDeChoc.h \
          include/uniteObstacleFactory.h \
          include/obstacles/obstacle.h \
          include/obstacles/terrainNu.h \
          include/obstacles/foret.h \
          include/obstacles/riviere.h \
          include/game/drapeau.h \
          include/game/cellule.h \
          include/game/joueur.h \
          include/game/plateau.h \
          include/game/kaptureGame.h \
          include/commands/command.h \
          include/commands/stop.h \
          include/commands/MoveCommand.h \
          include/commands/EndTurnCommand.h \
          include/game/TurnManager.h

OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Compilation principale avec gestion des fichiers d'en-tête
$(TARGET): $(OBJ_FILES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES)

# Compilation des fichiers objets (inclus les headers)
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Exécution du programme
run: $(TARGET)
	./$(TARGET)
