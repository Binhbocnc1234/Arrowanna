#include "GameManager.h"
#include "Player.h"
#include "Projectile.h"
#include "Boss.h"
#include "Ultilities.h"
#include "PauseMenu.h"
#include <iostream>

GameManager* GameManager::instance = nullptr;

// Thêm biến static hoặc thành viên (nếu muốn) cho pause
static bool isPaused = false;
static int musicVolume = 128;
static PauseButton pauseBtn(GameConfig::SCREEN_WIDTH - 60, 20, 40);
static PauseMenu* pauseMenu = nullptr;

GameManager* GameManager::getInstance(){
    return instance;
}
GameManager::GameManager() : gameState(GameState::BossTurn),
    player(GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT / 2 + 20, 3),
    boss(GameConfig::SCREEN_WIDTH/2, 60, 100),
    m_UIManager(GameConfig::renderer)
{
    InBossTurn();
    if (instance == nullptr){
        instance = this;
    }
    else{
        std::cerr << "Two or more instances of GameManager!" << std::endl;
    }
    // Init pause menu
    static TTF_Font* pauseFont = TTF_OpenFont("Assets/RadiantKingdom-mL5eV.ttf", 32);
    pauseMenu = new PauseMenu(GameConfig::renderer, pauseFont);
}

void GameManager::Update(){
    Uint32 currentTime = SDL_GetTicks();
    switch(gameState){
        case GameState::BossTurn:
            // Pause button logic
            {
                int mx, my;
                Uint32 mouseState = SDL_GetMouseState(&mx, &my);
                pauseBtn.hovered = pauseBtn.isHovered(mx, my);

                // Draw pause button
                pauseBtn.render(GameConfig::renderer);

                // Handle pause click
                static bool prevMouseDown = false;
                bool mouseDown = mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
                if (!isPaused && pauseBtn.isClicked(mx, my, mouseDown) && !prevMouseDown) {
                    isPaused = true;
                }
                prevMouseDown = mouseDown;
            }

            if (isPaused) {
                int result = pauseMenu->updateAndRender(musicVolume);
                // Mix_VolumeMusic(musicVolume);
                if (result == 0) { // Continue
                    isPaused = false;
                } else if (result == 1) { // Quit
                    GameConfig::running = false;
                }
                // Don't update game logic when paused
                SDL_RenderPresent(GameConfig::renderer);
                return;
            }

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
            if (currentTime - gameOverStart >= 5000){
                GameConfig::running = false;
            }
            break;
        case GameState::Win:
            m_UIManager.renderWin();
            player.update();
            if (currentTime - gameOverStart >= 5000){
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

