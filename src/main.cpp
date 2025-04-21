#include <SDL2/SDL.h>
#include <bits/stdc++.h>
#include "SDL2/SDL_mixer.h"
#include "Player.h"
#include "Boss.h"
#include "Wave.h"
#include "UIManager.h"
#include "GameManager.h"
#include "Explosion.h"

using namespace std;

const int SCREEN_WIDTH = GameConfig::SCREEN_WIDTH;
const int SCREEN_HEIGHT = GameConfig::SCREEN_HEIGHT;
const float frameDelay = 1000 / (float)GameConfig::FPS;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Arrowanna", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    GameConfig::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!GameConfig::renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    Mix_Music *background_music = Mix_LoadMUS("Assets/Sounds/Undie music.mp3");
    Mix_PlayMusic(background_music, -1);
    
    Projectile* debugProjectile = nullptr;  // Single debug projectile
    Explosion* debugExplosion = nullptr;   // Debug explosion pointer (local to main.cpp)

    GameManager gameManager;
    while (GameConfig::running) {
        float frameStart = SDL_GetTicks();

        // Handle SDL events to keep window open
        while (SDL_PollEvent(&GameConfig::e)) {
            if (GameConfig::e.type == SDL_QUIT) {
                GameConfig::running = false;
            }
            // Debug: trigger explosion on space
            if (GameConfig::IS_DEBUG_MODE && GameConfig::e.type == SDL_KEYDOWN && GameConfig::e.key.keysym.sym == SDLK_SPACE) {
                if (!debugExplosion) {
                    debugExplosion = new Explosion(Vector(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 20, 60, 80);
                }
            }
            gameManager.ProcessInput(GameConfig::e);
        }

        

        //Clear previous frame
        SDL_SetRenderDrawColor(GameConfig::renderer, 0, 0, 0, 255);
        SDL_RenderClear(GameConfig::renderer);

        LerpVectorController::Lerping();
        //GameManager
        gameManager.Update();

        // Debug: update and render explosion if exists
        if (debugExplosion) {
            float dt = frameDelay; // or use SDL_GetTicks() delta for more accuracy
            debugExplosion->update(dt);
            debugExplosion->render(GameConfig::renderer);
            if (!debugExplosion->isAlive()) {
                delete debugExplosion;
                debugExplosion = nullptr;
            }
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
    system("pause");
    return 0;
}
