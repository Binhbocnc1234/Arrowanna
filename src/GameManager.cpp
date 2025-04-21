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
    player(GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2 + 20, 3),
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
            m_UIManager.render(player.health, score, player.GetGoldEnergy(), GameConfig::MAX_ENERGY);
            break;
        case GameState::PlayerTurn:
            boss.update();
            player.updatePlayer();
            player.updateProjectile();
            m_UIManager.render(player.health, score, player.GetGoldEnergy(), GameConfig::MAX_ENERGY);
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
void GameManager::ProcessInput(SDL_Event e)
{
    if (GameConfig::e.type == SDL_QUIT) {
        GameConfig::running = false;
    }

    // Delegate to player input
    switch (gameState) {
        case GameState::BossTurn:
            player.HandleEvent(GameConfig::e);
            break;

        case GameState::PlayerTurn:
            player.HandleShoot(GameConfig::e);
            break;

        default:
            break;
    }
}

void GameManager::InPlayerTurn(){

    ChangeGameState(GameState::PlayerTurn);
    player.InPlayerTurn();
    boss.InPlayerTurn();
}
void GameManager::InBossTurn(){
    ChangeGameState(GameState::BossTurn);
    player.InBossTurn();
    boss.InBossTurn();
}
void GameManager::Win(){
    gameOverStart = SDL_GetTicks64();
    ChangeGameState(GameState::Win);

}
void GameManager::Lose(){
    gameOverStart = SDL_GetTicks64();
    ChangeGameState(GameState::Lose);
}
void GameManager::ChangeGameState(GameState state){
    gameState = state;
    cout << "New gameState: " << state << '\n';
}

