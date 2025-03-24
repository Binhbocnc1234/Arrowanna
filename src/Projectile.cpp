#include "Projectile.h"
#include "Player.h"
#include "GameManager.h"
#include <bits/stdc++.h>
using namespace std;

Projectile::Projectile(int startX, int startY, Direction dir, float sp)
    : direction(dir), gameObject(startX, startY), speed(sp) {
    gameObject.color = Color(255, 0, 0, 255);
    if (direction == Direction::UP || direction == Direction::DOWN) {
        gameObject.width = 10;
        gameObject.height = 30;
    } else {
        gameObject.width = 30;
        gameObject.height = 10;
    }
}


void Projectile::update() {
    switch (direction) {
        case Direction::UP: gameObject.direction = Vector(0, speed);break;
        case Direction::DOWN:  gameObject.direction = Vector(0, -speed); break;
        case Direction::LEFT:  gameObject.direction = Vector(speed, 0); break;
        case Direction::RIGHT: gameObject.direction = Vector(-speed, 0); break;
        case Direction::NONE:
            cout << "ERROR: direction is NONE\n";
            break;
    }
    gameObject.Translate();
    // cout << gameObject.position.x << ' ' << gameObject.position.y << '\n';
    if (hasHitPlayer() || hasHitShield() || isOffScreen()){
        isAlive = false;
    }
}

void Projectile::render(SDL_Renderer* renderer) {
    gameObject.RectRender();
}

bool Projectile::hasHitPlayer() {
    Player pl = *Player::getInstance();
    bool ans = pl.gameObject.IsCollide(gameObject.position); //Error!
    if (ans == true){
        pl.takeDamage(static_cast<int>(direction));
    }
    return ans;
}

bool Projectile::hasHitShield() {
    Player pl = *Player::getInstance();
    bool ans = (direction == pl.shieldDir && gameObject.position.GetDistance(pl.shieldObject.position) <= 15);
    if (ans){
        cout << "Arrow blocked!";
        GameManager::getInstance()->score += 1;
    }
    return ans;
}

bool Projectile::isOffScreen() {
    Vector p = gameObject.position;
    return (p.x < 0 || p.x > GameConfig::SCREEN_WIDTH || p.y < 0 || p.y > GameConfig::SCREEN_HEIGHT);
}
