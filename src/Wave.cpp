#include "Wave.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

Wave::Wave(int screenWidth, int screenHeight) 
    : screenWidth(GameConfig::SCREEN_WIDTH), screenHeight(screenHeight) {}
void Wave::spawnProjectile() {
    int randDir = rand() % 4;
    Direction dir = static_cast<Direction>(randDir);
    float speed = rand() % (1) + 3;

    int startX, startY;
    switch(dir){
        case Direction::LEFT:
            startX = 0;
            startY = screenHeight / 2;
            break;
        case Direction::RIGHT:
            startX = screenWidth;
            startY = screenHeight / 2;
            break;
        case Direction::UP:
            startX = screenWidth / 2;
            startY = 0;
            break;
        case Direction::DOWN:
            startX = screenWidth / 2;
            startY = screenHeight;
        default:
            break;
    }
    int type = rand() % 6;
    Projectile* projectile;
    if (type <= 4){
        projectile = new EnemyProjectile(startX, startY, dir, speed);
    }
    else{
        projectile = new BuffProjectile(startX, startY, dir, speed);
    }
    projectiles.push_back(projectile);
}
void Wave::update(){
    ++frameCount;
    // cout << "frameCount: " << frameCount << ' ';
    if (frameCount >= 60){
        frameCount = 0;
        cout << "Spawn\n";
        spawnProjectile();
    }
}
void Wave::updateProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        (*it)->update();  // Dereference pointer

        if (!(*it)->isAlive) {  // Check isAlive
            delete *it;         // Free memory
            it = projectiles.erase(it);  // Erase from vector
        } else {
            ++it;
        }
    }
    renderProjectiles();
}


void Wave::renderProjectiles() {
    for (auto& proj : projectiles)
    {
        proj->render(GameConfig::renderer);
    }
}
