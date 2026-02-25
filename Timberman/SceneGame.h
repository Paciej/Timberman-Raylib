#pragma once
#include "Scene.h"
#include "raylib.h"
import RayFunctions;

class Game;

class SceneGame : public Scene {
private:

    Texture2D gui;
    Texture2D easyTexture;
    Texture2D easyPressedTexture;
    Texture2D hardTexture;
    Texture2D hardPressedTexture;
    Game* game;
    //background variables
    float bgPosX = 1280 / 2 - 150;
    float bgPosY = 200;
    float bgWidth = 300;
    float bgHeight = 300;
    Rectangle bgSrcRec = getSpriteRec(6, 20, 3, 3);
    Rectangle bgRec = {bgPosX, bgPosY, bgWidth, bgHeight};

    //tile variables
    float tileWidth = 150;
    float tileHeight = 50;

    Rectangle easyDestRec = { bgPosX + 75, bgPosY + 80, tileWidth, tileHeight };
    Texture2D currentEasy;

    Rectangle hardDestRec = { bgPosX + 75, bgPosY + 150, tileWidth, tileHeight };
    Texture2D currentHard;
    bool chosenDifficulty = false;

public:
    SceneGame();
    virtual Scene* NextScene() const;
    virtual bool ShouldTransition() const;
    virtual void Update();
    virtual void Render();

    ~SceneGame() {
        delete game;
    }
};

