#ifndef BOSS_H
#define BOSS_H

#include "Ultilities.h"
#include "Wave.h"
#include "TextureLoader.h"
#include "HorizontalObstacle.h"
#include <vector>

class Boss {
public:
    static Boss *getInstance();
    std::vector<HorizontalObstacle*> obstacles;
    Boss(int x, int y, int health);
    void update();
    void renderBoss(SDL_Renderer* renderer);
    void InPlayerTurn();
    void InBossTurn();
    void GetDamage(int index);
    GameObject gameObject;
private:
    static Boss* instance;
    
    Wave wave;
    int health, maxHealth;
    std::vector<string> sprites;
    int currentSpriteIndex;
    Uint32 lastSpriteChangeTime;
};

#endif // BOSS_H
