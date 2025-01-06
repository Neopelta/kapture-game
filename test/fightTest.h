#ifndef FIGHTTEST_H
#define FIGHTTEST_H

#include <gtest/gtest.h>
#include "../include/units/unite.h"
#include "../include/units/eclaireur.h"
#include "../include/units/chairACanon.h"
#include "../include/units/troupeDeChoc.h"
#include "../include/game/kaptureGame.h"

class fightTest : public ::testing::Test {
protected:
    void SetUp() override {
        eclaireur1 = new kpt::eclaireur();
        eclaireur2 = new kpt::eclaireur();
        chairCanon = new kpt::chairACanon();
        chairCanon2 = new kpt::chairACanon();
        troupeChoc = new kpt::troupeDeChoc();
        troupeChoc2 = new kpt::troupeDeChoc();

        const std::pair<short unsigned int, short unsigned int> pos1 = {1, 1};
        const std::pair<short unsigned int, short unsigned int> pos2 = {1, 2};

        eclaireur1->operator^(pos1);
        eclaireur2->operator^(pos2);
        chairCanon->operator^(pos1);
        chairCanon2->operator^(pos2);
        troupeChoc->operator^(pos1);
        troupeChoc2->operator^(pos2);
    }

    void TearDown() override {
        delete eclaireur1;
        delete eclaireur2;
        delete chairCanon;
        delete chairCanon2;
        delete troupeChoc;
        delete troupeChoc2;
    }

    kpt::eclaireur* eclaireur1;
    kpt::eclaireur* eclaireur2;
    kpt::chairACanon* chairCanon;
    kpt::chairACanon* chairCanon2;
    kpt::troupeDeChoc* troupeChoc;
    kpt::troupeDeChoc* troupeChoc2;
};

#endif