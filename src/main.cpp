#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include "Player.h"
#include "Boss.h";
#include "Wave.h"
#include "UIManager.h"
#include "GameManager.h"

using namespace std;

const int SCREEN_WIDTH = GameConfig::SCREEN_WIDTH;
const int SCREEN_HEIGHT = GameConfig::SCREEN_HEIGHT;
const float frameDelay = 1000 / (float)GameConfig::FPS;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Arrowanna", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    GameConfig::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    GameManager gameManager;
    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3);
    Boss boss(SCREEN_WIDTH/2, 60);
    std::cout << "Player initialized at: " << player.gameObject << std::endl;
    Wave wave(SCREEN_WIDTH, SCREEN_HEIGHT);
    Projectile* debugProjectile = nullptr;  // Single debug projectile
    UIManager m_UIManager(GameConfig::renderer);

    bool running = true;
    SDL_Event e;
    while (running) {
        float frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            player.handleEvent(e);

            // Debug mode: Spawn a projectile from the top when LMB is clicked (if none exists)
            if (GameConfig::IS_DEBUG_MODE && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                if (debugProjectile == nullptr) { // Only one projectile allowed
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    debugProjectile = new EnemyProjectile(mouse_x, mouse_y, Direction::DOWN, 5.0f);
                    cout << "Spawned debug projectile at (" << mouse_x << ", 0)\n";
                }
            }
        }

        //Clear previous frame
        SDL_SetRenderDrawColor(GameConfig::renderer, 0, 0, 0, 255);
        SDL_RenderClear(GameConfig::renderer);
        // Update projectiles (regular mode or debug mode)
        if (!GameConfig::IS_DEBUG_MODE) {
            wave.update();
            wave.updateProjectiles();
        } else if (debugProjectile) {
            debugProjectile->update();
            if (!debugProjectile->isAlive) {
                delete debugProjectile;
                debugProjectile = nullptr;
                cout << "Debug projectile has been removed\n";
            }
        }
        ScreenShakeEffect::UpdateScreenShake();
        //Player
        player.update();
        //UI
        m_UIManager.render(player.health, gameManager.score);
        //GameManager
        gameManager.Update();
        //BOSS

        //GameOver handling
        if (gameManager.isGameOver){
            m_UIManager.renderGameOver();  // Show "YOU LOSE"
            SDL_RenderPresent(GameConfig::renderer);
            SDL_Delay(3000);  // Wait 3 seconds
            running = false;
        }
        //Update screen with any renderings performed since the previous call
        SDL_RenderPresent(GameConfig::renderer);

        // FPS control
        float frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyRenderer(GameConfig::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
