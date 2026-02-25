#pragma once
#include "raylib.h"
#include <string>
#include <filesystem>
export module AudioManager;

 export Music getMusicFromName(const std::string musicName) {
    std::filesystem::path musicPath = std::filesystem::current_path() / "Resources" / "Sounds" / musicName;
    if (!std::filesystem::exists(musicPath)) {
        TraceLog(LOG_ERROR, TextFormat("Texture file not found: %s", musicPath.string().c_str()));
        return Music{}; // Zwraca pust¹ teksturê
    }
    return LoadMusicStream(musicPath.string().c_str());
}

 export Sound getSoundFromName(const std::string soundName) {
     std::filesystem::path soundPath = std::filesystem::current_path() / "Resources" / "Sounds" / soundName;
     if (!std::filesystem::exists(soundPath)) {
         TraceLog(LOG_ERROR, TextFormat("Texture file not found: %s", soundPath.string().c_str()));
         return Sound{}; // Zwraca pust¹ teksturê
     }
     return LoadSound(soundPath.string().c_str());
 }

export class AudioManager {
private:
    static bool isInit;
    static bool musicMuted;
    static bool soundMuted;
public:
    static Music currentTheme;
    static Music mainTheme;
    static Music background;

    static void initAudio() {
        if (!isInit) {
            InitAudioDevice();
            isInit = true;
        }
    }

    static void playSoundEffect(Sound sound) {
        if (!soundMuted) {
            PlaySound(sound);
        }
    }

    static void playMainTheme(Music music = currentTheme) {
        currentTheme = music;
        PlayMusicStream(music);
    }

    static void changeMainTheme(Music music) {
        StopMusicStream(currentTheme);
        UnloadMusicStream(currentTheme);
        currentTheme = music;
        playMainTheme(currentTheme);
    }

    static void closeMusic() {
        UnloadMusicStream(AudioManager::currentTheme);
        CloseAudioDevice();
        isInit = false;
    }

    static void setSoundMuted(bool m) {
        soundMuted = m;
    }

    static void setMusicMuted(bool m) {
        musicMuted = m;
    }

    static bool soundIsMuted() {
        return soundMuted;
    }

    static bool musicIsMuted() {
        return musicMuted;
    }
};

bool AudioManager::soundMuted = false;
bool AudioManager::musicMuted = false;
bool AudioManager::isInit = false;

Music AudioManager::mainTheme = getMusicFromName("main_theme.mp3");
Music AudioManager::background = getMusicFromName("background.mp3");
Music AudioManager::currentTheme = AudioManager::mainTheme;
