#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Ultilities.h"

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

private:
    static Player *instance;
};

#endif
