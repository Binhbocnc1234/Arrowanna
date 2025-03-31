#pragma once
#include <string>
#include <unordered_map>
#include "SDL2/SDL.h"



class TextureLoader
{
public:
	static SDL_Texture* loadTexture(std::string filename);
	static std::vector<SDL_Texture*> loadSprites(std::string filename, int count, int width, int height);
	static void deallocateTextures();


private:
	static std::unordered_map<std::string, SDL_Texture*> umapTexturesLoaded;
};