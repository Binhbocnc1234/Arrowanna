#pragma once
#include "Ultilities.h"

class GameManager{
public:
    static GameManager *getInstance();
    GameManager();
    void Update();
    void PlayerTurn();
    int score = 0;
    bool isGameOver;

private:
    static GameManager *instance;
};

