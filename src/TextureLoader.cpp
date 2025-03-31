#include "TextureLoader.h"
#include "Ultilities.h"
#include <iostream>
#include <SDL2/SDL_image.h>
using namespace std;

std::unordered_map<std::string, SDL_Texture*> TextureLoader::umapTexturesLoaded;

SDL_Texture* TextureLoader::loadTexture(std::string filename) {
    SDL_Renderer* renderer = GameConfig::renderer;
    if (filename != "") {
        auto found = umapTexturesLoaded.find(filename);

        if (found != umapTexturesLoaded.end()) {
            return found->second;
        } else {
            std::string filepath = "Assets/Images/" + filename + ".png";
            SDL_Surface* surfaceTemp = IMG_Load(filepath.c_str());

            if (surfaceTemp != nullptr) {
                SDL_Texture* textureOutput = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
                SDL_FreeSurface(surfaceTemp);

                if (textureOutput != nullptr) {
                    SDL_SetTextureBlendMode(textureOutput, SDL_BLENDMODE_BLEND);
                    umapTexturesLoaded[filename] = textureOutput;
                    return textureOutput;
                }
            } else {
                cerr << "Image file not found: " << filepath << endl;
            }
        }
    }
    return nullptr;
}

std::vector<SDL_Texture*> TextureLoader::loadSprites(std::string filename, int count, int width, int height) {
    std::vector<SDL_Texture*> sprites;
    SDL_Renderer* renderer = GameConfig::renderer;
    std::string filepath = "Assets/Images/" + filename + ".png";

    SDL_Surface* surfaceTemp = IMG_Load(filepath.c_str());
    if (!surfaceTemp) {
        cerr << "Image file not found: " << filepath << endl;
        return sprites;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
    SDL_FreeSurface(surfaceTemp);
    if (!texture) {
        cerr << "Failed to create texture from: " << filepath << endl;
        return sprites;
    }

    for (int i = 0; i < count; ++i) {
        SDL_Texture* sprite = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
        SDL_SetRenderTarget(renderer, sprite);
        SDL_Rect srcRect = { i * width, 0, width, height };
        SDL_RenderCopy(renderer, texture, &srcRect, nullptr);
        SDL_SetRenderTarget(renderer, nullptr);
        sprites.push_back(sprite);
        umapTexturesLoaded[filename + "_" + to_string(i)] = sprite;
    }

    SDL_DestroyTexture(texture);
    return sprites;
}

void TextureLoader::deallocateTextures() {
    while (!umapTexturesLoaded.empty()) {
        auto it = umapTexturesLoaded.begin();
        if (it->second != nullptr)
            SDL_DestroyTexture(it->second);
        umapTexturesLoaded.erase(it);
    }
}
