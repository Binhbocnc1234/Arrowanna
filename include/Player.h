#pragma once
#include <bits/stdc++.h>
#include "Ultilities.h"
#include "Projectile.h"
using namespace std;

enum PlayerTurnState
{
    WaitingToFire,
    Released,
    ProjectileDestroyed
};
class Player{
public:
    static Player *getInstance();
    static constexpr int HURT_ANIMATION_DURATION = 500;
    static constexpr int HURT_ANIMATION_DELAY = 100;

    Player(int x, int y, int health);
    void HandleEvent(SDL_Event& e);
    void HandleShoot(SDL_Event &e);
    void update();
    void updatePlayer();
    void updateShield();
    void updateProjectile();
    void SetPlayerTurnState(PlayerTurnState state);
    void takeDamage(int projectileDir, int damage = 1);
    void ReceiveGoldEnergy();
    int GetGoldEnergy();
    void Shoot();
    void InPlayerTurn();
    void InBossTurn();
    bool isAlive() const;
    void PlayGetEnergySound();
    void PlayBlockSound();

    int health;
    Direction shieldDir;
    GameObject gameObject;
    GameObject shieldObject, oldShieldObject;

private:
    
    static Player *instance;
    bool isHurt = false;
    int goldEnergy;
    Direction oldShieldDir; 
    Uint32 shieldTransitionStart = 0;
    bool isShieldTransitioning = false;
    Uint32 hurtAnimationStart = 0;
    Vector origin;

    PlayerProjectile projectile; // Only one player projectile at a time
    PlayerTurnState playerTurnState;
    Uint32 projDestroyedTime = 0;
    bool pendingPlayerTurn = false; // <-- Add this line
};
