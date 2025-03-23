#include <SDL2/SDL.h>
#include "Player.h"
#include "Wave.h"
#include <bits/stdc++.h>
using namespace std;

const int SCREEN_WIDTH = GameConfig::SCREEN_WIDTH;
const int SCREEN_HEIGHT = GameConfig::SCREEN_HEIGHT;
const float frameDelay = 1000 / (float)GameConfig::FPS;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Arrowanna", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    GameConfig::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3);
    std::cout << "Player initialized at: " << player.gameObject << std::endl;
    Wave wave(SCREEN_WIDTH, SCREEN_HEIGHT);
    Projectile* debugProjectile = nullptr;  // Single debug projectile

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
                    debugProjectile = new Projectile(mouse_x, mouse_y, Direction::DOWN, 5.0f);
                    cout << "Spawned debug projectile at (" << mouse_x << ", 0)\n";
                }
            }
        }

        // Update projectiles (regular mode or debug mode)
        if (!GameConfig::IS_DEBUG_MODE) {
            wave.update();
            wave.updateProjectiles();
        } else if (debugProjectile) {
            debugProjectile->update();
            if (!debugProjectile->isAlive) {
                delete debugProjectile;
                debugProjectile = nullptr;
                cout << "Debug projectile removed\n";
            }
        }

        SDL_SetRenderDrawColor(GameConfig::renderer, 0, 0, 0, 255);
        SDL_RenderClear(GameConfig::renderer);

        player.update();

        if (!GameConfig::IS_DEBUG_MODE) {
            wave.renderProjectiles();
        } else if (debugProjectile) {
            debugProjectile->render(GameConfig::renderer);
        }

        SDL_RenderPresent(GameConfig::renderer);

        float frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    // Clean up if debug projectile still exists
    if (debugProjectile) {
        delete debugProjectile;
    }

    SDL_DestroyRenderer(GameConfig::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
