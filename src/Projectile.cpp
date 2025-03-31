#include "Projectile.h"
#include "Player.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

Projectile::Projectile() : gameObject(0, 0), direction(Direction::UP) {}

Projectile::Projectile(int startX, int startY, Direction dir, float sp, Color color, int width, int height)
    : direction(dir), gameObject(startX, startY), speed(sp) {
    gameObject.color = color;
    gameObject.width = width;
    gameObject.height = height;
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
    }
    return ans;
}
// EnemyProjectile keeps its behavior of increasing score when Player blocks an EnemyProjectile successfully
bool EnemyProjectile::hasHitShield() {
    if (Projectile::hasHitShield()) {
        cout << "Arrow blocked!\n";
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
        GameManager::getInstance()->PlayerTurn();
        return true;
    }
    return false;
}