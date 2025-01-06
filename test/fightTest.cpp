#include "fightTest.h"
#include "../include/game/joueur.h"

using namespace kpt;

TEST_F(fightTest, testFightScoutvsScout) {
    EXPECT_EQ(eclaireur1->fight(*eclaireur2), unitInteraction::DRAW)
        << "Le combat entre éclaireurs devrait être un match nul";
}

TEST_F(fightTest, testFightCannonFoddervsScout) {
    EXPECT_EQ(chairCanon->fight(*eclaireur1), unitInteraction::LOST)
        << "L'éclaireur (défenseur) perd contre la chair à canon";

    EXPECT_EQ(eclaireur1->fight(*chairCanon), unitInteraction::WON)
        << "La chair à canon (défenseur) gagne contre l'éclaireur";
}

TEST_F(fightTest, testFightShockTroopvsScout) {
    EXPECT_EQ(troupeChoc->fight(*eclaireur1), unitInteraction::LOST)
        << "L'éclaireur (défenseur) perd contre la troupe de choc";

    EXPECT_EQ(eclaireur1->fight(*troupeChoc), unitInteraction::WON)
        << "La troupe de choc (défenseur) gagne contre l'éclaireur";
}

TEST_F(fightTest, testFightShockTroopvsCannonFodder) {
    EXPECT_EQ(troupeChoc->fight(*chairCanon), unitInteraction::LOST)
        << "La chair à canon (défenseur) perd contre la troupe de choc";

    // Point de vue de la troupe de choc (défenseur)
    EXPECT_EQ(chairCanon->fight(*troupeChoc), unitInteraction::WON)
        << "La troupe de choc (défenseur) gagne contre la chair à canon";
}

TEST_F(fightTest, testFightCannonFoddervsCannonFodder) {
    unitInteraction result = chairCanon->fight(*chairCanon2);
    EXPECT_TRUE(result == unitInteraction::WON || result == unitInteraction::LOST)
        << "Le combat entre chairs à canon doit donner une victoire ou une défaite";
}

TEST_F(fightTest, testFightShockTroopvsShockTroop) {
    EXPECT_EQ(troupeChoc->fight(*troupeChoc2), unitInteraction::DRAW)
        << "Les troupes de choc doivent avoir un match nul et reculer";
}

TEST_F(fightTest, testFightWithFlags) {
    kaptureGame<8, 8> *game = kaptureGame<8, 8>::getInstance(2);
    ASSERT_NE(game, nullptr) << "Le jeu n'a pas été créé correctement";

    auto& players = game->getPlayers();
    ASSERT_GE(players.size(), 1) << "Au moins un joueur requis";

    joueur& player = players.at(0);

    std::pair<short unsigned int, short unsigned int> pos1 = {1, 1};
    std::pair<short unsigned int, short unsigned int> pos2 = {1, 2};

    troupeChoc->operator^(pos1);
    troupeChoc->operator()(pos1.first, pos1.second);
    eclaireur1->operator^(pos2);
    eclaireur1->operator()(pos2.first, pos2.second);

    try {
        drapeau flag;
        flag.operator()(pos1);
        player.operator()(flag);

        game->assignFlag(player, troupeChoc);

        ASSERT_NE(troupeChoc->operator*(), nullptr)
            << "Le drapeau n'a pas été correctement assigné à l'unité";

        auto result = eclaireur1->fight(*troupeChoc);
        EXPECT_EQ(result, unitInteraction::DRAW)
            << "Combat entre éclaireur et unité avec drapeau doit être un match nul";
    }
    catch (const std::exception& e) {
        FAIL() << "Exception inattendue : " << e.what();
    }

    delete game;
}