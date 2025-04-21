#include "Wave.h"
#include "Player.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

Wave::Wave(){
    width = GameConfig::SCREEN_WIDTH;
    height = GameConfig::SCREEN_HEIGHT;
    updateModeSettings();
}
Wave::Wave(int width, int height) : width(width), height(height){
    updateModeSettings();
}

void Wave::setMode(WaveMode newMode) {
    mode = newMode;
    updateModeSettings();
}

WaveMode Wave::getMode() const {
    mode;
}

void Wave::updateModeSettings() {
    switch (mode) {
        case WaveMode::NORMAL:
            spawnDelay = 60;
            projectileSpeed = 3.0f;
            break;
        case WaveMode::HYPED:
            spawnDelay = 80; // Longer delay
            projectileSpeed = 7.0f; // Faster
            break;
        case WaveMode::SLOWMOTION:
            spawnDelay = 40; // Shorter delay
            projectileSpeed = 1.5f; // Slower
            break;
        case WaveMode::TRICKY_ONLY:
            spawnDelay = 70;
            projectileSpeed = 4.0f;
            break;
    }
    // Reset mode timer when mode changes
    modeTimer = 0;
}

void Wave::spawnProjectile() {
    int randDir = rand() % 4;
    Direction dir = static_cast<Direction>(randDir);
    float speed = projectileSpeed;

    // Calculate wave boundaries
    int left = (GameConfig::SCREEN_WIDTH - width) / 2;
    int right = left + width;
    int top = (GameConfig::SCREEN_HEIGHT - height) / 2;
    int bottom = top + height;

    int startX, startY;
    switch(dir){
        case Direction::LEFT:
            startX = left;
            startY = Player::getInstance()->gameObject.position.y;
            // Clamp Y inside boundaries
            if (startY < top) startY = top;
            if (startY > bottom) startY = bottom;
            break;
        case Direction::RIGHT:
            startX = right;
            startY = Player::getInstance()->gameObject.position.y;
            if (startY < top) startY = top;
            if (startY > bottom) startY = bottom;
            break;
        case Direction::UP:
            startX = Player::getInstance()->gameObject.position.x;
            startY = top;
            if (startX < left) startX = left;
            if (startX > right) startX = right;
            break;
        case Direction::DOWN:
            startX = Player::getInstance()->gameObject.position.x;
            startY = bottom;
            if (startX < left) startX = left;
            if (startX > right) startX = right;
            break;
        default:
            startX = left; startY = top; break;
    }

    Projectile* projectile;
    if (mode == WaveMode::TRICKY_ONLY) {
        projectile = new TrickyProjectile(startX, startY, dir, speed);
    } else {
        int type = rand() % 11; // 0-5: Enemy, 6-7: Buff, 8: Health, 9: Tricky
        if (type <= 6){
            projectile = new EnemyProjectile(startX, startY, dir, speed);
        }
        else if (type <= 8){
            projectile = new BuffProjectile(startX, startY, dir, speed);
        }
        else if (type <= 9){
            projectile = new HealthProjectile(startX, startY, dir, speed);
        }
        else { // type == 10
            projectile = new TrickyProjectile(startX, startY, dir, speed);
        }
    }
    projectiles.push_back(projectile);
    cout << projectiles.size() << '\n';
}

void Wave::update(){
    ++frameCount;

    // Mode timer logic
    ++modeTimer;
    if (modeTimer >= modeDuration) {
        modeTimer = 0;
        nextMode();
    }

    if (frameCount >= spawnDelay){
        frameCount = 0;
        cout << "Spawn\n";
        spawnProjectile();
    }
    updateProjectiles();
    renderBoundaries();
}

void Wave::updateProjectiles() {
    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
        (*it)->update();
        if (!(*it)->isAlive) {
            delete *it;
            it = projectiles.erase(it);
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

void Wave::renderBoundaries() {
    // Centered main rectangle
    SDL_Rect boundary = {
        (GameConfig::SCREEN_WIDTH - width) / 2,
        (GameConfig::SCREEN_HEIGHT - height) / 2,
        width,
        height
    };

    SDL_Renderer* renderer = GameConfig::renderer;
    // Draw 4 thick white borders (top, bottom, left, right)
    const int thickness = 5;
    //Set white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Top border
    SDL_Rect top = { boundary.x, boundary.y, boundary.w, thickness };
    SDL_RenderFillRect(renderer, &top);
    // Bottom border
    SDL_Rect bottom = { boundary.x, boundary.y + boundary.h - thickness, boundary.w, thickness };
    SDL_RenderFillRect(renderer, &bottom);
    // Left border
    SDL_Rect left = { boundary.x, boundary.y, thickness, boundary.h };
    SDL_RenderFillRect(renderer, &left);
    // Right border
    SDL_Rect right = { boundary.x + boundary.w - thickness, boundary.y, thickness, boundary.h };
    SDL_RenderFillRect(renderer, &right);
}

void Wave::clearProjectiles(){
    for (auto* p : projectiles) {
        delete p;
    }
    projectiles.clear();
}

// Add helper to cycle to the next mode
void Wave::nextMode() {
    switch (mode) {
        case WaveMode::NORMAL:
            setMode(WaveMode::HYPED);
            break;
        case WaveMode::HYPED:
            setMode(WaveMode::SLOWMOTION);
            break;
        case WaveMode::SLOWMOTION:
            setMode(WaveMode::NORMAL);
            break;
        case WaveMode::TRICKY_ONLY:
            setMode(WaveMode::NORMAL);
            break;
    }
}
