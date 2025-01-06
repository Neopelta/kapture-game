#include "kaptureGameTest.h"

using namespace kpt;

kaptureGameTest::kaptureGameTest() {
    game = nullptr;
}

kaptureGameTest::kaptureGameTest(const kaptureGameTest &kgTest) {
    game = kgTest.game;
}

kaptureGameTest &kaptureGameTest::operator=(const kaptureGameTest &kgTest) {
    if (this != &kgTest) {
        delete game;
        game = kgTest.game;
    }
    return *this;
}

TEST_F(kaptureGameTest, testVisionFields) {
    std::vector<joueur> players = game->operator()();
    joueur &firstPlayer = players.at(0);
    joueur &secondPlayer = players.at(1);

    std::vector<std::pair<short, short>> spaces = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (unite* unit : *firstPlayer) {
        game->updateVisionFields(firstPlayer, unit);
    }

    for (cellule *c : ***game) {
        for (const unite *u : *firstPlayer) {
            std::pair<short unsigned int, short unsigned int> coords = !(*u);
            for (const std::pair<short, short> &delta: spaces) {
                const short unsigned newX = coords.first + delta.first;
                const short unsigned newY = coords.second + delta.second;

                if (newX < 10 && newY < 10) {
                    const cellule *refCell = game->operator*().operator*().at(newX * 10 + newY);
                    ASSERT_TRUE(refCell->isVisible(firstPlayer));
                    ASSERT_FALSE(refCell->isVisible(secondPlayer));
                }
            }
        }
    }
}

TEST_F(kaptureGameTest, testStolerManagment) {
    std::vector<joueur> players = game->operator()();
    joueur &firstPlayer = players.at(0);
    joueur &secondPlayer = players.at(1);

    drapeau d = !firstPlayer;

    unite *u = firstPlayer.operator*().at(10);
    const std::pair<short unsigned int, short unsigned int> uniteCoord = !(*u);
    const cellule *c = game->operator*().operator[](uniteCoord.first * 10 + uniteCoord.second);

    ASSERT_TRUE(c->isVisible(firstPlayer));
    ASSERT_FALSE(c->isVisible(secondPlayer));

    game->assignFlag(secondPlayer, u);

    for (const joueur &p : players)
        ASSERT_TRUE(c->isVisible(p));

}
