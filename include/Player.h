#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Ultilities.h"
#include <bits/stdc++.h>
using namespace std;

class Player{
public:
    static Player *getInstance();
    
    Player(int x, int y, int health);
    void handleEvent(SDL_Event& e);
    void update();
    void takeDamage(int projectileDir);
    bool isAlive() const;

    int health;
    GameObject gameObject;
    GameObject shieldObject;
    Direction shieldDir;

    // function<void<int>> OnBlocked
private:
    static Player *instance;
};

#endif
