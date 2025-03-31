#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Ultilities.h"
#include <bits/stdc++.h>
using namespace std;

class Player{
public:
    static Player *getInstance();
    static constexpr int HURT_ANIMATION_DURATION = 500;
    static constexpr int HURT_ANIMATION_DELAY = 100;
    
    Player(int x, int y, int health);
    void handleEvent(SDL_Event& e);
    void update();
    void takeDamage(int projectileDir);
    bool isAlive() const;

    int health;
    GameObject gameObject;
    GameObject shieldObject, oldShieldObject;

    Direction shieldDir, oldShieldDir; 
    Uint32 shieldTransitionStart = 0;
    bool isShieldTransitioning = false;

    // function<void<int>> OnBlocked
private:
    static Player *instance;
};

#endif
