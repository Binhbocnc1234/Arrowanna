#include "MusicAndSoundLoader.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

// Define static members
std::unordered_map<std::string, Mix_Music*> MusicAndSoundLoader::musicMap;
std::unordered_map<std::string, Mix_Chunk*> MusicAndSoundLoader::soundMap;

// Helper function to get sound path and check existence
static std::string GetSoundPath(const std::string& filename) {
    std::string path = "Assets/Sounds/" + filename + ".mp3";
    std::ifstream f(path.c_str());
    if (!f.good()) {
        std::cerr << "Sound file not found: " << path << std::endl;
    }
    return path;
}

Mix_Music* MusicAndSoundLoader::LoadMusic(const std::string& filename) {
    auto it = musicMap.find(filename);
    if (it != musicMap.end()) return it->second;
    std::string path = GetSoundPath(filename);
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (music) musicMap[filename] = music;
    return music;
}

Mix_Chunk* MusicAndSoundLoader::LoadSound(const std::string& filename) {
    auto it = soundMap.find(filename);
    if (it != soundMap.end()) return it->second;
    std::string path = GetSoundPath(filename);
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (chunk) soundMap[filename] = chunk;
    return chunk;
}
