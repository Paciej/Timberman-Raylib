#include "raylib.h"
import <vector>;
export module ResManager;

#pragma once
export struct Resolution {
    int width;
    int height;
    const char* label;
};

export class ResManager {
private:
    static int screenWidth;
    static int screenHeight;
    static bool needRestart;
public:
    static const std::vector<Resolution>& GetAvailableResolutions() {
        static std::vector<Resolution> resolutions = {
            { 800, 600, "800x600" },
            { 1280, 720, "1280x720" },
            { 1600, 900, "1600x900" },
            { 1920, 1080, "1920x1080" }
        };
        return resolutions;
    }

    static void ApplyResolution(int width, int height) {
        screenWidth = width;
        screenHeight = height;
        needRestart = true;
    }
    static int GetWidth() { return screenWidth; }
    static int GetHeight() { return screenHeight; }
    static bool NeedsRestart() {
        if (needRestart) {
            needRestart = false;
            return true;
        }
        return false;
    }
};

int ResManager::screenWidth = 1920;
int ResManager::screenHeight = 1080;
bool ResManager::needRestart = false;
