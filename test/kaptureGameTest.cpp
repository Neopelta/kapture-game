//
// Created by maxime on 22/12/24.
//

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

    game->updateVisionFields(firstPlayer);

    for (cellule &c : ***game) {
        for (const unite *u : *firstPlayer) {
            std::pair<short unsigned int, short unsigned int> coords = !(*u);
            for (const std::pair<short, short> &delta: spaces) {
                const short unsigned newX = coords.first + delta.first;
                const short unsigned newY = coords.second + delta.second;

                if (newX < 10 && newY < 10) {
                    cellule refCell = game->operator*().operator*().at(newX * 10 + newY);
                    ASSERT_TRUE(refCell.isVisible(firstPlayer));
                    ASSERT_FALSE(refCell.isVisible(secondPlayer));
                }
            }
        }
    }
}
