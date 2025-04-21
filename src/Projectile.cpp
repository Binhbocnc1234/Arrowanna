#include "Projectile.h"
#include "Player.h"
#include "Boss.h"
#include "GameManager.h"
#include "Explosion.h"
#include <iostream>
using namespace std;

Explosion* currentExplosion = nullptr;

Projectile::Projectile() : gameObject(0, 0), direction(Direction::UP) {}

Projectile::Projectile(int startX, int startY, Direction dir, float sp, Color color, int width, int height)
    : direction(dir), gameObject(startX, startY, width, height), speed(sp) {
    gameObject.color = color;
}

void Projectile::update() {
    switch (direction) {
        case Direction::UP:    gameObject.direction = Vector(0, speed); break;
        case Direction::DOWN:  gameObject.direction = Vector(0, -speed); break;
        case Direction::LEFT:  gameObject.direction = Vector(speed, 0); break;
        case Direction::RIGHT: gameObject.direction = Vector(-speed, 0); break;
        case Direction::NONE:
            cout << "ERROR: direction is NONE\n";
            break;
    }
    gameObject.Translate();

    if (hasHitPlayer() || hasHitShield() || isOffScreen()) {
        isAlive = false;
        cout << "Projectile destroyed\n";
    }
}

void Projectile::render(SDL_Renderer* renderer) {
    gameObject.RectRender();
}
bool Projectile::hasHitPlayer() {
    return Player::getInstance()->gameObject.IsCollide(gameObject.position);
}
bool Projectile::hasHitShield() {
    Player* pl = Player::getInstance();
    return (direction == pl->shieldDir && gameObject.position.GetDistance(pl->shieldObject.position) <= 15);
}
bool Projectile::isOffScreen() {
    Vector p = gameObject.position;
    return (p.x < 0 || p.x > GameConfig::SCREEN_WIDTH || p.y < 0 || p.y > GameConfig::SCREEN_HEIGHT);
}

/// ENEMY PROJECTILE

EnemyProjectile::EnemyProjectile(int startX, int startY, Direction dir, float sp)
    : Projectile(startX, startY, dir, sp, Color(255, 0, 0, 255), (dir == Direction::LEFT || dir == Direction::RIGHT) ? 30 : 10, (dir == Direction::UP || dir == Direction::DOWN) ? 30 : 10) {}

bool EnemyProjectile::hasHitPlayer() {
    Player* pl = Player::getInstance();
    bool ans = pl->gameObject.IsCollide(gameObject.position);
    if (ans) {
        ScreenShakeEffect::StartScreenShake();
        pl->takeDamage(static_cast<int>(direction));
        cout << "Projectile hit Player\n";
    }
    
    return ans;
}
// EnemyProjectile keeps its behavior of increasing score when Player blocks an EnemyProjectile successfully
bool EnemyProjectile::hasHitShield() {
    if (Projectile::hasHitShield()) {
        Player::getInstance()->PlayBlockSound();
        GameManager::getInstance()->score += 1;
        return true;
    }
    return false;
}

/// BUFF PROJECTILE

BuffProjectile::BuffProjectile(int startX, int startY, Direction dir, float sp)
    : Projectile(startX, startY, dir, sp, Color(255, 255, 0, 255), 10, 10) {}

bool BuffProjectile::hasHitPlayer() {
    if (Projectile::hasHitPlayer()){
        Player::getInstance()->ReceiveGoldEnergy();
        return true;
    }
    return false;
}

// PLAYER PROJECTILE
PlayerProjectile::PlayerProjectile(int startX, int startY, float sp) : 
    Projectile(startX, startY, Direction::DOWN, sp, Color(255,69,0, 255), 40, 40) {

}
void PlayerProjectile::update(){
    Projectile::update();
    hasHitBoss();
}
bool PlayerProjectile::hasHitPlayer(){
    return false;
}
bool PlayerProjectile::hasHitBoss(){
    if (gameObject.IsCollide(Boss::getInstance()->gameObject)){
        Boss::getInstance()->TakeDamage(5);
        // Create explosion at boss center if none exists
        if (!currentExplosion) {
            currentExplosion = new Explosion(gameObject.position);
        }
        isAlive = false;
        return true;
    }
    return false;
}
bool PlayerProjectile::hasHitShield(){
    for(auto ob : Boss::getInstance()->obstacles){
        if (ob->gameObject.IsCollide(gameObject)){
            Boss::getInstance()->TakeDamage(ob->index);
            // Create explosion at collision point if none exists
            if (!currentExplosion) {
                currentExplosion = new Explosion(gameObject.position);
            }
            isAlive = false;
            return true;
        }
    }
    return false;
}


void PlayerProjectile::render(SDL_Renderer* renderer) {
    // Draw trail effect (downward)
    int trailLength = 6;
    float trailAlphaStep = 40.0f;
    Vector pos = gameObject.position;
    for (int i = 1; i <= trailLength; ++i) {
        SDL_SetRenderDrawColor(renderer, 255, 140, 0, Uint8(255 - i * trailAlphaStep));
        SDL_Rect trailRect = {
            static_cast<int>(pos.x - gameObject.width/2),
            static_cast<int>(pos.y - gameObject.height/2 + i * 12), // <-- Downward
            gameObject.width, gameObject.height
        };
        SDL_RenderFillRect(renderer, &trailRect);
    }
    // Draw main projectile
    gameObject.RectRender();
}

/// HEALTH PROJECTILE

HealthProjectile::HealthProjectile(int startX, int startY, Direction dir, float sp)
    : Projectile(startX, startY, dir, sp, Color(255, 255, 255, 255), 22, 22) // Small size, white color
{
    gameObject.mainTextureName = "player"; // Use "player.png" as heart
}

bool HealthProjectile::hasHitPlayer() {
    if (Projectile::hasHitPlayer()) {
        Player::getInstance()->health++; // Directly increase health
        std::cout << "Player gained health! Health: " << Player::getInstance()->health << std::endl;
        return true;
    }
    return false;
}

void HealthProjectile::update() {
    // Animate scale (zoom in/out)
    animTime += 0.1f;
    scale = 1.0f + 0.2f * sin(animTime * 2.0f); // oscillate between 0.8 and 1.2

    // Update size for animation
    int baseW = 16, baseH = 16;
    gameObject.width = static_cast<int>(baseW * scale);
    gameObject.height = static_cast<int>(baseH * scale);

    Projectile::update();
}

void HealthProjectile::render(SDL_Renderer* renderer) {
    // Use texture render (with current width/height)
    gameObject.TextureRender();
}

/// TRICKY PROJECTILE

TrickyProjectile::TrickyProjectile(int startX, int startY, Direction dir, float speed)
    // Use EnemyProjectile's color and size
    : Projectile(startX, startY, dir, speed, Color(255, 0, 0, 255), 
        (dir == Direction::LEFT || dir == Direction::RIGHT) ? 30 : 10, 
        (dir == Direction::UP || dir == Direction::DOWN) ? 30 : 10), 
      originalDir(dir)
{
    // Tricky projectile now looks like EnemyProjectile
}

bool TrickyProjectile::isNearPlayer() {
    Vector playerPos = Player::getInstance()->gameObject.position;
    float dist = gameObject.position.GetDistance(playerPos);
    return dist < 120.0f && !switchedLane && !isOffScreen();
}

void TrickyProjectile::startLaneSwitch() {
    switchedLane = true;
    animStartPos = gameObject.position;

    // Pick a new lane (direction) different from original
    do {
        newDir = static_cast<Direction>(rand() % 4);
    } while (newDir == originalDir);

    // Set animation end position: align with player, but on new lane
    Vector playerPos = Player::getInstance()->gameObject.position;
    switch (newDir) {
        case Direction::UP:    animEndPos = Vector(playerPos.x, 80); break;
        case Direction::DOWN:  animEndPos = Vector(playerPos.x, GameConfig::SCREEN_HEIGHT-80); break;
        case Direction::LEFT:  animEndPos = Vector(80, playerPos.y); break;
        case Direction::RIGHT: animEndPos = Vector(GameConfig::SCREEN_WIDTH-80, playerPos.y); break;
        default: animEndPos = animStartPos; break;
    }
    // Swap width/height if changing between vertical and horizontal
    bool wasVertical = (originalDir == Direction::UP || originalDir == Direction::DOWN);
    bool nowHorizontal = (newDir == Direction::LEFT || newDir == Direction::RIGHT);
    bool wasHorizontal = (originalDir == Direction::LEFT || originalDir == Direction::RIGHT);
    bool nowVertical = (newDir == Direction::UP || newDir == Direction::DOWN);
    if ((wasVertical && nowHorizontal) || (wasHorizontal && nowVertical)) {
        std::swap(gameObject.width, gameObject.height);
    }
    switchAnimProgress = 0.0f;
}

void TrickyProjectile::update() {
    if (!switchedLane && isNearPlayer()) {
        startLaneSwitch();
    }

    if (switchedLane && switchAnimProgress < 1.0f) {
        // Animate lane switch (lerp from animStartPos to animEndPos)
        switchAnimProgress += 0.08f; // Animation speed
        if (switchAnimProgress > 1.0f) switchAnimProgress = 1.0f;
        gameObject.position = animStartPos.Lerp(animEndPos, switchAnimProgress);
        if (switchAnimProgress >= 1.0f) {
            // After animation, set new direction and continue
            direction = newDir;
            // Set position exactly to end
            gameObject.position = animEndPos;
        }
    } else if (!switchedLane || (switchedLane && switchAnimProgress >= 1.0f)) {
        // Normal movement in current direction
        Projectile::update();
    }
}

void TrickyProjectile::render(SDL_Renderer* renderer) {
    // Draw a trail during lane switch
    if (switchedLane && switchAnimProgress < 1.0f) {
        SDL_SetRenderDrawColor(renderer, 180, 120, 255, 120);
        SDL_Rect trailRect = { 
            static_cast<int>(gameObject.position.x - gameObject.width/2),
            static_cast<int>(gameObject.position.y - gameObject.height/2),
            gameObject.width, gameObject.height
        };
        SDL_RenderFillRect(renderer, &trailRect);
    }
    gameObject.RectRender();
}

bool TrickyProjectile::hasHitPlayer() {
    return Projectile::hasHitPlayer();
}
bool TrickyProjectile::hasHitShield() {
    return Projectile::hasHitShield();
}

// At the end of your main render/update loop (e.g., in GameManager or main.cpp):
// Update and render the single explosion if it exists
// if (currentExplosion) {
//     float dt = ...; // time since last frame in ms
//     currentExplosion->update(dt);
//     currentExplosion->render(GameConfig::renderer);
//     if (!currentExplosion->isAlive()) {
//         delete currentExplosion;
//         currentExplosion = nullptr;
//     }
// }