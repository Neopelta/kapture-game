#include "../include/uniteObstacleFactory.h"

#include <regex>

#include "../include/game/drapeau.h"
#include "../include/obstacles/foret.h"
#include "../include/obstacles/riviere.h"
#include "../include/obstacles/terrainNu.h"
#include "../include/units/chairACanon.h"
#include "../include/units/eclaireur.h"
#include "../include/units/troupeDeChoc.h"
#include "../include/units/unite.h"

kpt::unitObstacle* kpt::uniteObstacleFactory::createEntity(const std::string &data,
                                                          const std::pair<short unsigned int, short unsigned int> &pos) {
    if (std::regex_match(data, std::regex("[\\.FR]"))) {
        unitObstacle *entity;
        if (data == ".")
            entity = new terrainNu;
        else if (data == "F")
            entity = new foret;
        else
            entity = new riviere;
        entity->operator^(pos);
        return entity;
    }
    if (data.substr(0, 1) == "D") {
        drapeau *flag = new drapeau;
        flag->operator^(pos);
        flag->operator()();
        return flag;
    }

    unite *unit;
    if (data.substr(0, 1) == "E")
        unit = new eclaireur;
    else if (data.substr(0, 1) == "C")
        unit = new chairACanon;
    else
        unit = new troupeDeChoc;

    // On initialise une seule fois l'unité
    unit->operator^(pos);
    unit->reset();
    return unit;  // Retourne l'unité originale
}
