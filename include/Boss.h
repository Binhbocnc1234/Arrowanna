#ifndef BOSS_H
#define BOSS_H

#include "Ultilities.h"
#include "Wave.h"
#include "TextureLoader.h"
#include "HorizontalObstacle.h"
#include "Laser.h"
#include "DamageObject.h"
#include <vector>

class Boss {
public:
    static Boss *getInstance();
    std::vector<HorizontalObstacle*> obstacles;
    std::vector<DamageObject*> damageObjects;
    Boss(int x, int y, int health);
    void update();
    void renderBoss(SDL_Renderer* renderer);
    void InPlayerTurn();
    void InBossTurn();
    int GetHealth() const;
    void TakeDamage(int amount);
    void tryActivateLaser();
    GameObject gameObject;
    const int maxHealth;
    Laser* laser = nullptr;

private:
    static Boss* instance;
    
    Wave wave;
    int health;
    std::vector<string> sprites;
    int currentSpriteIndex;
    Uint32 lastSpriteChangeTime;
};

#endif // BOSS_H
