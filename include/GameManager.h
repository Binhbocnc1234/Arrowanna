#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#pragma once

class GameManager{
public:
    static GameManager *getInstance();
    GameManager();
    // UpdateScore();
    int score = 0;


private:
    static GameManager *instance;
};

#endif