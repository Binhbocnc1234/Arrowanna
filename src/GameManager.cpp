#include "GameManager.h"
#include "Projectile.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;
GameManager* GameManager::getInstance(){
    return instance;
}
GameManager::GameManager(){

    if (instance == nullptr){
        instance = this;
    }
    else{
        std::cerr << "Two or more instances of Singleton!" << std::endl;
    }
}
