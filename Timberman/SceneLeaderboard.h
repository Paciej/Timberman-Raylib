#include "Scene.h"
#include "raylib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
import RayFunctions;

#pragma once
class SceneLeaderboard : public Scene {
private:
    struct ScoreEntry {
        int score;
        std::string nickname;

        bool operator<(const ScoreEntry& other) const {
            return score > other.score;
        }
    };

    std::vector<ScoreEntry> topTenScores = {};
    
    //background variables
    float woodWidth = 400;
    float woodHeight = 500;
    float bgPosX = 0.5 * (1280 - woodWidth);
    float bgPosY = 100;
    Rectangle bgDestRec = { bgPosX, bgPosY, woodWidth, woodHeight };
    Rectangle bgSourceRec = getSpriteRec(6, 20, 3, 3);
    Texture2D bgTexture;

    //text variables
    float textPosX = bgPosX + 80;
    float textPosY = bgPosY + 60;

    // home button variables
    float buttonWidth = 70;
    float buttonHeight = buttonWidth;
    float buttonPosX = bgPosX;
    float buttonPosY = woodHeight + buttonHeight + 30;
    Rectangle buttonDestRec = { buttonPosX, buttonPosY, buttonWidth, buttonHeight };
    Rectangle buttonSrcRec = getSpriteRec(1, 20);
    Rectangle buttonPressedSrcRec = getSpriteRec(1, 21);
    Rectangle currentButton = buttonSrcRec;

    bool backToMenu = false;

    std::string fileName = "Scoreboard.txt";

    std::vector<ScoreEntry> loadScoresFromFile(const std::string& filename);
    std::vector<ScoreEntry> getTop10Scores();
public:
    SceneLeaderboard() {
        bgTexture = getTextureFromAssetName("gui.png");

        if (!std::filesystem::exists(fileName)) {
            std::ofstream file(fileName);
            if (!file) {
                std::cerr << "ERROR: Plik tekstowy " << fileName << " nie istnieje i nie moze zostac utworzony";
                backToMenu = true;
            }
            file.close();
        }

        topTenScores = getTop10Scores();
    }

    virtual Scene* NextScene() const;
    virtual bool ShouldTransition() const;
    virtual void Update();
    virtual void Render();
};

