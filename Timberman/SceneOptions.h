#pragma once
#include "Scene.h"
#include "raylib.h"
#include <vector>
#include <string>
import ResManager;
import AudioManager;
import RayFunctions;

class SceneOptions : public Scene {
private:
    Texture2D gui;
    
    //background variables
    float bgWidth = 400;
    float bgHeight = 400;
    float bgPosX = 0.5 * (1280 - bgWidth);
    float bgPosY = 150;
    Rectangle bgRec = { bgPosX, bgPosY, bgWidth, bgHeight };
    Rectangle bgSrcRec = getSpriteRec(6, 20, 3, 3);

    // music mute variables
    float musicMuteWidth = 70;
    float musicMuteHeight = musicMuteWidth;
    float musicMutePosX = bgPosX + 100;
    float musicMutePosY = bgPosY + 70;
    Rectangle musicMuteDestRec = { musicMutePosX, musicMutePosY, musicMuteWidth, musicMuteHeight };
    Rectangle musicMuteSrcRec = getSpriteRec(5, 18);
    Rectangle musicMutePressedSrcRec = getSpriteRec(6, 19);
    Rectangle currentMusicMute;

    // sound mute variables
    float boxWidth = musicMuteWidth;
    float boxHeight = boxWidth;
    float boxPosX = bgPosX + bgWidth - 100 - boxWidth;
    float boxPosY = musicMutePosY;
    Rectangle boxRec = { boxPosX, boxPosY, boxWidth, boxHeight };
    Rectangle boxSrcRec = getSpriteRec(7, 18);
    Rectangle boxPressedSrcRec = getSpriteRec(8, 19);
    Rectangle currentBox;
    Color boxCol;

    //resolution variables
    float resWidth = 150;
    float resHeight = 50;
    float resPosX = 0.5 * (1280 - resWidth);
    float resPosY = (bgPosY + 170);
    Rectangle resRec = { resPosX, resPosY, resWidth, resHeight };
    Rectangle resSrcRec = getSpriteRec(6, 20, 3, 3);

    // Arrows variables
    float arrowWidth = resHeight;
    float arrowHeight = resHeight;
    Rectangle arrowLeft = { resPosX - arrowWidth, resPosY, resHeight, resHeight };
    Rectangle arrowLeftSrc = getSpriteRec(1, 0);
    Rectangle arrowLeftPressedSrc = getSpriteRec(1, 1);
    Rectangle arrowRight = { resPosX + resWidth, resPosY, resHeight, resHeight };
    Rectangle arrowRightSrc = getSpriteRec(2, 0);
    Rectangle arrowRightPressedSrc = getSpriteRec(2, 1);
    Rectangle currentArrowLeft = arrowLeftSrc;
    Rectangle currentArrowRight = arrowRightSrc;


    //submit box variables
    float applyWidth = 100;
    float applyHeight = 40;
    float applyPosX = 0.5 * (1280 - applyWidth);
    float applyPosY = resPosY + 60;
    Rectangle applyRec = { applyPosX, applyPosY, applyWidth, applyHeight };
    Color applyCol = GRAY;
    Texture2D submitTexture;
    Texture2D submitPressedTexture;
    Texture2D currentSubmit;


    // home button variables
    float buttonWidth = 70;
    float buttonHeight = buttonWidth;
    float buttonPosX = bgPosX;
    float buttonPosY = bgPosY + bgHeight + 20;
    Rectangle buttonDestRec = { buttonPosX, buttonPosY, buttonWidth, buttonHeight };
    Rectangle buttonSrcRec = getSpriteRec(1, 20);
    Rectangle buttonPressedSrcRec = getSpriteRec(1, 21);
    Rectangle currentButton = buttonSrcRec;

    std::vector<Resolution> allRes = ResManager::GetAvailableResolutions();
    int maxOption = allRes.size();
    int currentOption;
    std::string currentRes;

    bool backToMenu = false;
public:
    SceneOptions() {
        gui = getTextureFromAssetName("gui.png");
        submitTexture = getTextureFromAssetName("submit.png");
        submitPressedTexture = getTextureFromAssetName("submitPressed.png");
        currentSubmit = submitTexture;

        bool isMuted = AudioManager::soundIsMuted();
        currentBox = (isMuted) ? boxPressedSrcRec : boxSrcRec;
        isMuted = AudioManager::musicIsMuted();
        currentMusicMute = (isMuted) ? musicMutePressedSrcRec : musicMuteSrcRec;

        for (size_t i = 0; i < allRes.size(); i++) {
            if (GetScreenWidth() == allRes[i].width) {
                currentOption = i;
                currentRes = allRes[i].label;
            }
        }
    }

    virtual Scene* NextScene() const;
    virtual bool ShouldTransition() const;
    virtual void Update();
    virtual void Render();
};

