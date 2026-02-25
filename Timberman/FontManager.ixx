#include "raylib.h"
export module FontManager;

export class FontManager {
private:
    static Font gameFont;
    static Font pressedFont;
public:
    static void LoadAssets() {
        gameFont = LoadFont("Resources/Fonts/Wood.png");
        pressedFont = LoadFont("Resources/Fonts/WoodPressed.png");
    };

    static Font& GetFont() {
        return gameFont;
    };

    static Font& GetPressedFont() {
        return pressedFont;
    }
};

Font FontManager::gameFont = {};
Font FontManager::pressedFont = {};