#pragma once
#include "SceneMenu.h"
#include <fstream>
import RayFunctions;

#define MAX_INPUT_CHARS     10

class SceneOver : public Scene {
private:
    bool backToMenu = false;
    bool scoreIsSaved = false;
    bool insertNickname = false;
    int gameScore;

    // background variables
    float backWidth = 500;
    float backHeight = 450;
    float backPosX = 0.5 * (1280 - backWidth);
    float lowBackPosY = 616;
    Rectangle backDestRec = { backPosX, 216, backWidth, backHeight };
    Rectangle backSrcRec = getSpriteRec(6, 20, 3, 3);
    Texture2D gui;

    //text box variables
    float textBoxWidth = 300;
    float textBoxHeight = 60;
    Rectangle textBox = { backPosX + 100, lowBackPosY - textBoxHeight - 170, textBoxWidth, textBoxHeight };
    char nickname[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    bool nickIsValid = false;

    // statement variables
    std::string answer = "";
    int frameCounter = 0;

    //buttons variables
	Texture2D replayTexture;
    float replayWidth = 120;
    float replayHeight = 90;
	Texture2D menuTexture;
    float menuWidth = 120;
    float menuHeight = 90;
    Rectangle replayRec = { backPosX + 75, lowBackPosY - replayHeight - 40, replayWidth, replayHeight};
    Rectangle menuRec = { backPosX + backWidth - 75 - menuWidth, lowBackPosY - menuHeight - 40, menuWidth, menuHeight};
    Color replayCol = YELLOW;
    Color menuCol = GRAY;

    //leaderboard file
    std::ofstream scoreFile;

    void insertText(Vector2& mousePos);
    std::string nicknameAccuracyText(char newNickname[MAX_INPUT_CHARS + 1]);
public:
    bool playAgain = false;

    SceneOver(int score) : gameScore(score) {
        gui = getTextureFromAssetName("gui.png");
        replayTexture = getTextureFromAssetName("restart.png");
        menuTexture = getTextureFromAssetName("home.png");

        scoreFile.open("Scoreboard.txt", std::ios::app);

        if (!scoreFile) {
            std::cerr << "\nERROR: nie mozna otworzyc pliku z tabela wynikow";
            exit(1);
        }
    }
    SceneOver() {}

    virtual Scene* NextScene() const;
    virtual bool ShouldTransition() const;
    virtual void Update();
    virtual void Render();

    ~SceneOver() {
        scoreFile.close();
    }
};

