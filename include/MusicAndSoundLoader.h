#ifndef MUSICANDSOUNDLOADER_H
#define MUSICANDSOUNDLOADER_H

#include <string>
#include <unordered_map>
#include "SDL2/SDL_mixer.h"

class MusicAndSoundLoader {
public:
    // Loads a music file from Assets/Sounds/<filename>.mp3
    static Mix_Music* LoadMusic(const std::string& filename);

    // Loads a sound effect from Assets/Sounds/<filename>.mp3
    static Mix_Chunk* LoadSound(const std::string& filename);

private:
    static std::unordered_map<std::string, Mix_Music*> musicMap;
    static std::unordered_map<std::string, Mix_Chunk*> soundMap;
};

#endif // MUSICANDSOUNDLOADER_H
