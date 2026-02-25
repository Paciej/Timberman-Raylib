#include "Scene.h"
#include "SceneGame.h"
#include "SceneLeaderboard.h"
#include "SceneOptions.h"
import RayFunctions;
import FontManager;
#pragma once

class SceneMenu : public Scene {
private:
    enum class Scenes {
        none,
        gameScene,
        leaderboardScene,
        optionScene,
        Exit
    };

    struct Tile {
        Vector2 tilePos;
        Rectangle sourceRec;
        Rectangle destRec;
        Scenes tileScene;
    };

    Texture2D gui;
    Texture2D titleTexture;
    //Font mainFont = FontManager::GetFont();
    //Font pressedFont = FontManager::GetPressedFont();
    //Font currentFont = mainFont;

    //title variables
    float gameTitleWidth = 500;
    float gameTitleHeight = 70;
    float gameTitleOffset = gameTitleWidth / 2;

    //background variables
    float woodWidth = 500;
    float woodHeight = 400;
    float woodOffset = woodWidth / 2;
    Rectangle woodRec = getSpriteRec(6, 20, 3, 3);

    //tile variables
    float tileWidth = 200;
    float tileHeight = tileWidth / 3;
    float tileOffset = tileWidth / 2;
    Rectangle startRec = getSpriteRec(5, 10, 4);
    Rectangle startPressedRec = getSpriteRec(5, 11, 4);
    Rectangle scoreRec = getSpriteRec(5, 33, 3, 1);
    Rectangle scorePressedRec = getSpriteRec(5, 34, 3, 1);
    Rectangle settingsRec = getSpriteRec(5, 2, 4);
    Rectangle settingsPressedRec = getSpriteRec(5, 3, 4);
    Rectangle exitRec = getSpriteRec(5, 16, 3);
    Rectangle exitPressedRec = getSpriteRec(5, 17, 3);
    Texture2D score;
    Texture2D scorePressed;
    Texture2D currentScore = score;

    std::vector<Tile> tilesVec;
    std::vector<Rectangle> tileRectangles = {startRec, startPressedRec, scoreRec, scorePressedRec, settingsRec, settingsPressedRec, exitRec, exitPressedRec};
    bool changeScene = false;
    Scenes selectedScene = Scenes::none;

    //private functions
    void createTiles();
public:
    SceneMenu() {
        gui = getTextureFromAssetName("gui.png");
        score = getTextureFromAssetName("score.png");
        scorePressed = getTextureFromAssetName("scorePressed.png");
        titleTexture = getTextureFromAssetName("title.png");
        createTiles();
    }

    bool ShouldTransition() const override;
    Scene* NextScene() const override;
    void Update() override;
    void Render() override;
};