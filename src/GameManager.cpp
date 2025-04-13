#include "GameManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Boss.h"
#include "Ultilities.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance(){
    return instance;
}
GameManager::GameManager() : gameState(GameState::BossTurn),
    player(GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2 + 60, 3),
    boss(GameConfig::SCREEN_WIDTH/2, 60, 100),
    m_UIManager(GameConfig::renderer)
{
    if (instance == nullptr){
        instance = this;
    }
    else{
        std::cerr << "Two or more instances of GameManager!" << std::endl;
    }
}

void GameManager::Update(){
    Uint32 currentTime = SDL_GetTicks();
    switch(gameState){
        case GameState::BossTurn:
            boss.update();
            player.updatePlayer();
            player.updateShield();
            player.HandleEvent(GameConfig::e);
            m_UIManager.render(player.health, score, player.goldEnergy, Player::MAX_ENERGY);
            break;
        case GameState::PlayerTurn:
            boss.update();
            player.updatePlayer();
            player.HandleShoot(GameConfig::e);
            break;
        case GameState::Lose:
            m_UIManager.renderGameOver();
            boss.update();
            if (currentTime - gameOverStart >= 3000){
                GameConfig::running = false;
            }

            break;
        case GameState::Win:
            m_UIManager.renderWin();
            player.update();
            if (currentTime - gameOverStart >= 3000){
                GameConfig::running = false;
            }
            break;
    }
}

void GameManager::InPlayerTurn(){
    cout << "Player turn\n";
    player.InPlayerTurn();
    boss.InPlayerTurn();
}
void GameManager::InBossTurn(){
    cout << "Boss turn\n";
    player.InBossTurn();
    boss.InBossTurn();
}
void GameManager::Win(){
    gameOverStart = SDL_GetTicks64();
    ChangeGameState(GameState::Win);

}
void GameManager::Lose(){
    ChangeGameState(GameState::Lose);
}
void GameManager::ChangeGameState(GameState state){
    gameState = state;
    cout << "New gameState: " << state << '\n';
}

