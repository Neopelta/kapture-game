#include "fightTest.h"

#include "../../../../include/units/chairACanon.h"
#include "../include/units/troupeDeChoc.h"

using namespace kpt;

TEST_F(fightTest, testFightScoutvsScout) {
    eclaireur e1 = eclaireur();
    eclaireur e2 = eclaireur();

    ASSERT_EQ(e1.fight(e2), unitInteraction::DRAW);
}

TEST_F(fightTest, testFightCannonFoddervsScout) {
    eclaireur e = eclaireur();
    chairACanon c = chairACanon();
    ASSERT_EQ(e.fight(c), unitInteraction::WON);
    ASSERT_EQ(c.fight(e), unitInteraction::LOST);
}

TEST_F(fightTest, testFightShockTroopvsScout) {
    eclaireur e = eclaireur();
    troupeDeChoc t = troupeDeChoc();
    ASSERT_EQ(e.fight(t), unitInteraction::WON);
    ASSERT_EQ(t.fight(e), unitInteraction::LOST);
}

TEST_F(fightTest, testFightShockTroopvsCannonFodder) {
    troupeDeChoc t = troupeDeChoc();
    chairACanon c = chairACanon();
    ASSERT_EQ(c.fight(t), unitInteraction::WON);
    ASSERT_EQ(t.fight(c), unitInteraction::LOST);
}

// there is not a test on the fight between two cannons fodders because the result of the fight depends on a random factor

TEST_F(fightTest, testShockTroopvsShockTroopMoveBackOneCell) {
    kaptureGame<10, 10> *game = kaptureGame<10, 10>::getInstance(2);

    const std::pair<short unsigned int, short unsigned int> firstCoord = {5, 4};
    const std::pair<short unsigned int, short unsigned int> secondCoord = {5, 5};

    troupeDeChoc *t1 = new troupeDeChoc();
    troupeDeChoc *t2 = new troupeDeChoc();

    // assignment of coords
    t1->operator^(firstCoord);
    t2->operator^(secondCoord);
    t1->operator&();
    t2->operator&();

    // set up units in the board
    *(**game)[firstCoord.first * 10 + firstCoord.second]->operator=(t1);
    *(**game)[secondCoord.first * 10 + secondCoord.second]->operator=(t2);

    game->handleFight(t1, t2);

    cellule *newCellT1 = game->operator*().operator[](firstCoord.first * 10 + firstCoord.second - 1);
    cellule *newCellT2 = game->operator*().operator[](secondCoord.first * 10 + secondCoord.second - 1);

    ASSERT_EQ(newCellT1->operator->()->asciiArtPrint(), t1->asciiArtPrint());
    ASSERT_EQ(newCellT2->operator->()->asciiArtPrint(), t2->asciiArtPrint());

    delete game;
    delete t1;
    delete t2;
}

TEST_F(fightTest, testShockTroopvsShockTroopComeBackInSpawn) {
    kaptureGame<10, 10> *game = kaptureGame<10, 10>::getInstance(2);

    const std::pair<short unsigned int, short unsigned int> initialCoordT1 = {5, 4};
    const std::pair<short unsigned int, short unsigned int> initialCoordT2 = {5, 5};

    troupeDeChoc *t1 = new troupeDeChoc();
    troupeDeChoc *t2 = new troupeDeChoc();

    t1->operator^(initialCoordT1);
    t2->operator^(initialCoordT2);

    const std::pair<short unsigned int, short unsigned int> currentCoordT1 = {2, 0};
    const std::pair<short unsigned int, short unsigned int> currentCoordT2 = {3, 0};

    // set up current coordinates
    t1->operator()(currentCoordT1.first, currentCoordT1.second);
    t2->operator()(currentCoordT2.first, currentCoordT2.second);

    // set up units in the board
    *(**game)[currentCoordT1.first * 10 + currentCoordT1.second]->operator=(t1);
    *(**game)[currentCoordT2.first * 10 + currentCoordT2.second]->operator=(t2);

    cellule *spawnCellT1 = game->operator*().operator[](initialCoordT1.first * 10 + initialCoordT1.second);
    cellule *spawnCellT2 = game->operator*().operator[](initialCoordT2.first * 10 + initialCoordT2.second);

    // each unit is not in the own spawn
    ASSERT_NE(spawnCellT1->operator->()->asciiArtPrint(), t1->asciiArtPrint());
    ASSERT_NE(spawnCellT2->operator->()->asciiArtPrint(), t2->asciiArtPrint());

    game->handleFight(t1, t2);

    // now, it is the case
    ASSERT_EQ(spawnCellT1->operator->()->asciiArtPrint(), t1->asciiArtPrint());
    ASSERT_EQ(spawnCellT2->operator->()->asciiArtPrint(), t2->asciiArtPrint());

    delete game;
    delete t1;
    delete t2;
}

TEST_F(fightTest, testCannonFoddervsCannonFodderWithOneStealer) {
    kaptureGame<10, 10> *game = kaptureGame<10, 10>::getInstance(2);

    joueur &p1 = game->operator()().at(0);
    chairACanon *c1 = new chairACanon;
    chairACanon *c2 = new chairACanon;


    game->assignFlag(p1, c1);

    ASSERT_EQ(c2->fight(*c1), unitInteraction::LOST);
    ASSERT_EQ(c1->fight(*c2), unitInteraction::WON);

    delete c1;
    delete c2;
    delete game;
}

TEST_F(fightTest, testShockTroopvsScoutWithOneStealer) {
    kaptureGame<10, 10> *game = kaptureGame<10, 10>::getInstance(2);

    joueur &p1 = game->operator()().front();
    troupeDeChoc *t = new troupeDeChoc;
    eclaireur *e = new eclaireur;


    game->assignFlag(p1, t);

    ASSERT_EQ(t->fight(*e), unitInteraction::LOST);
    ASSERT_EQ(e->fight(*t), unitInteraction::DRAW);

    delete t;
    delete e;
    delete game;
}

TEST_F(fightTest, testShockTroopvsShockTroopWithOneStealer) {
    kaptureGame<10, 10> *game = kaptureGame<10, 10>::getInstance(2);

    joueur &p1 = game->operator()().front();
    troupeDeChoc *t1 = new troupeDeChoc;
    troupeDeChoc *t2 = new troupeDeChoc;


    game->assignFlag(p1, t1);

    ASSERT_EQ(t2->fight(*t1), unitInteraction::LOST);

    delete t1;
    delete t2;
    delete game;
}

