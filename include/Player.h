#pragma once
#include <bits/stdc++.h>
#include "Ultilities.h"
#include "Projectile.h"
using namespace std;

class Player{
public:
    static Player *getInstance();
    static constexpr int HURT_ANIMATION_DURATION = 500;
    static constexpr int HURT_ANIMATION_DELAY = 100;
    static constexpr int MAX_ENERGY = 6;

    Player(int x, int y, int health);
    void HandleEvent(SDL_Event& e);
    void HandleShoot(SDL_Event &e);
    void update();
    void updatePlayer();
    void updateShield();
    void takeDamage(int projectileDir);
    void GetGoldEnergy();
    void Shoot();
    void InPlayerTurn();
    void InBossTurn();
    bool isAlive() const;

    int health, goldEnergy;
    Direction shieldDir;
    GameObject gameObject;
    GameObject shieldObject, oldShieldObject;

private:
    
    static Player *instance;
    bool isHurt = false;
    Direction oldShieldDir; 
    Uint32 shieldTransitionStart = 0;
    bool isShieldTransitioning = false;
    Uint32 hurtAnimationStart = 0;
    Vector origin;
    PlayerProjectile projectile;
};
