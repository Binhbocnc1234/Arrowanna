#include "GameManager.h"
#include "Player.h"
#include "Projectile.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;
GameManager* GameManager::getInstance(){
    return instance;
}
GameManager::GameManager() : isGameOver(false){

    if (instance == nullptr){
        instance = this;
    }
    else{
        std::cerr << "Two or more instances of GameManager!" << std::endl;
    }
}
void GameManager::Update(){
    if (Player::getInstance()->health == 0){
        isGameOver = true;
    }
}
void GameManager::PlayerTurn(){
    cout << "Player turn\n";
}