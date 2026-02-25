#include "SceneOptions.h"
#include "SceneMenu.h"
import RayFunctions;

Scene* SceneOptions::NextScene() const {
    return new SceneMenu();
}

bool SceneOptions::ShouldTransition() const {
    return backToMenu;
}

void SceneOptions::Update()
{
    if (IsKeyPressed(KEY_B)) {
        backToMenu = true;
    }

    Vector2 mousePos = getMouseVirtualPosition();

    if (CheckCollisionPointRec(mousePos, buttonDestRec)) {
        currentButton = buttonPressedSrcRec;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            backToMenu = true;
        }
    }
    else {
        currentButton = buttonSrcRec;
    }

    if (CheckCollisionPointRec(mousePos, boxRec)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentBox = (currentBox.y == boxSrcRec.y) ? boxPressedSrcRec : boxSrcRec;
            AudioManager::setSoundMuted((currentBox.y == boxPressedSrcRec.y) ? true : false);
        }
    }

    if (CheckCollisionPointRec(mousePos, musicMuteDestRec)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentMusicMute = (currentMusicMute.y == musicMuteSrcRec.y) ? musicMutePressedSrcRec : musicMuteSrcRec;
            AudioManager::setMusicMuted((currentMusicMute.y == musicMutePressedSrcRec.y) ? true : false);
        }
    }


    if (CheckCollisionPointRec(mousePos, arrowLeft)) {
        currentArrowLeft = arrowLeftPressedSrc;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentOption -= 1;
            if (currentOption < 0) {
                currentOption = allRes.size() - 1;
            }
            currentRes = allRes[currentOption].label;
        }
    }
    else if (CheckCollisionPointRec(mousePos, arrowRight)) {
        currentArrowRight = arrowRightPressedSrc;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentOption += 1;
            if (currentOption >= allRes.size()) {
                currentOption = 0;
            }
            currentRes = allRes[currentOption].label;
        }
    }
    else {
        currentArrowLeft = arrowLeftSrc;
        currentArrowRight = arrowRightSrc;
    }

    if (GetScreenWidth() != allRes[currentOption].width) {
        if (CheckCollisionPointRec(mousePos, applyRec)) {
            currentSubmit = submitPressedTexture;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                ResManager::ApplyResolution(allRes[currentOption].width, allRes[currentOption].height);
            }
        }
    }
    else {
        currentSubmit = submitTexture;
    }
}

void SceneOptions::Render() {

    //DrawRectangleRec(bgRec, BROWN);
    DrawTexturePro(gui, bgSrcRec, bgRec, { 0, 0 }, 0.0f, WHITE);
    //DrawText("Mute", boxRec.x - 200, boxRec.y - 10, 30, WHITE);
    // DrawRectangleRec(boxRec, boxCol);
    DrawTexturePro(gui, currentMusicMute, musicMuteDestRec, { 0, 0 }, 0.0f, WHITE);
    DrawTexturePro(gui, currentBox, boxRec, { 0,0 }, 0.0f, WHITE);
    //DrawRectangleRec(resRec, WHITE);
    DrawTexturePro(gui, resSrcRec, resRec, { 0, 0 }, 0.0f, WHITE);
    DrawText(currentRes.c_str(), resPosX + 20, resPosY + 10, 25, WHITE);
    DrawTexturePro(gui, currentArrowLeft, arrowLeft, { 0,0 }, 0.0f, WHITE);
    DrawTexturePro(gui, currentArrowRight, arrowRight, { 0,0 }, 0.0f, WHITE);
    //DrawRectangleRec(arrowLeft, arrowLeftCol);
    //DrawRectangleRec(arrowRight, arrowRightCol);
    DrawTexturePro(gui, currentButton, buttonDestRec, { 0, 0 }, 0.0f, WHITE);

    if (GetScreenWidth() != allRes[currentOption].width) {
        //DrawRectangleRec(applyRec, applyCol);
        DrawTexturePro(currentSubmit, {0, 0, (float)currentSubmit.width, (float)currentSubmit.height}, applyRec, {0,0}, 0.0f, WHITE);
    }
}
