#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include "SDL2/SDL_mixer.h"
#include "Player.h"
#include "Boss.h"
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
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    Mix_Music *background_music = Mix_LoadMUS("Assets/Sounds/Undie music.mp3");
    Mix_PlayMusic(background_music, -1);
    
    Projectile* debugProjectile = nullptr;  // Single debug projectile
    
    
    GameManager gameManager;
    while (GameConfig::running) {
        float frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&GameConfig::e)) {
            if (GameConfig::e.type == SDL_QUIT) GameConfig::running = false;
            
            // Debug mode: Spawn a projectile from the top when LMB is clicked (if none exists)
            // if (GameConfig::IS_DEBUG_MODE && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            //     if (debugProjectile == nullptr) { // Only one projectile allowed
            //         int mouse_x, mouse_y;
            //         SDL_GetMouseState(&mouse_x, &mouse_y);
            //         debugProjectile = new EnemyProjectile(mouse_x, mouse_y, Direction::DOWN, 5.0f);
            //         cout << "Spawned debug projectile at (" << mouse_x << ", 0)\n";
            //     }
            // }
        }

        //Clear previous frame
        SDL_SetRenderDrawColor(GameConfig::renderer, 0, 0, 0, 255);
        SDL_RenderClear(GameConfig::renderer);
        // Update projectiles (regular mode or debug mode)

        // if (!GameConfig::IS_DEBUG_MODE) {
        //     wave.update();
        //     wave.updateProjectiles();
        // } else if (debugProjectile) {
        //     debugProjectile->update();
        //     if (!debugProjectile->isAlive) {
        //         delete debugProjectile;
        //         debugProjectile = nullptr;
        //         cout << "Debug projectile has been removed\n";
        //     }
        // }

        // ScreenShakeEffect::UpdateScreenShake();
        LerpVectorController::Lerping();
        //GameManager
        gameManager.Update();
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
