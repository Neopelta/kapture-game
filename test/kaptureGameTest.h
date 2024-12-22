#ifndef KAPTUREGAMETEST_H
#define KAPTUREGAMETEST_H


#include <gtest/gtest.h>

#include "../include/game/kaptureGame.h"

class kaptureGameTest : public ::testing::Test {
public:
    ~kaptureGameTest() override  =default;
    kaptureGameTest();
    kaptureGameTest(const kaptureGameTest &kgTest);
    kaptureGameTest& operator=(const kaptureGameTest &kgTest);
protected:
    void SetUp() override {
        game = kpt::kaptureGame<10,10>::getInstance(2);
        game->initializeGame();
    }

    void TearDown() override {
        delete game;
    }

    kpt::kaptureGame<10,10> *game;
};



#endif
