#include "SceneGame.h"
#include "Game.h"

SceneGame::SceneGame() : game(new Game(1, 1.5f, 20.f)) {
	gui = getTextureFromAssetName("gui.png");
	easyTexture = getTextureFromAssetName("easy.png");
	easyPressedTexture = getTextureFromAssetName("easyPressed.png");
	hardTexture = getTextureFromAssetName("hard.png");
	hardPressedTexture = getTextureFromAssetName("hardPressed.png");
	currentEasy = easyTexture;
	currentHard = hardTexture;
}

Scene* SceneGame::NextScene() const
{
	return new SceneMenu();
}

bool SceneGame::ShouldTransition() const {
	return game->backToMenu;
}

void SceneGame::Update()
{
	if (!chosenDifficulty) {
		Vector2 virtualMouse = getMouseVirtualPosition();
		if (CheckCollisionPointRec(virtualMouse, easyDestRec)) {
			currentEasy = easyPressedTexture;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				chosenDifficulty = true;
			}
		}
		else {
			currentEasy = easyTexture;
		}
		if (CheckCollisionPointRec(virtualMouse, hardDestRec)) {
			currentHard = hardPressedTexture;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				delete game;
				game = new Game(2, 2.5f, 28.f);
				chosenDifficulty = true;
			}
		} else {
			currentHard = hardTexture;
		}
	}
	else {
		//AudioManager::changeMainTheme(AudioManager::background);
		game->update();
	}
}

void SceneGame::Render()
{
	if (!chosenDifficulty) {
		//draw background
		DrawTexturePro(gui, bgSrcRec, bgRec, { 0,0 }, 0.0f, WHITE);
		//DrawRectangleRec(bgRec, BROWN);

		//draw tiles
		DrawTexturePro(currentEasy, {0, 0, (float)currentEasy.width, (float)currentEasy.height}, easyDestRec, {0,0}, 0.0f, WHITE);
		DrawTexturePro(currentHard, { 0, 0, (float)currentHard.width, (float)currentHard.height }, hardDestRec, { 0,0 }, 0.0f, WHITE);

		//DrawRectangleRec(easyRec, YELLOW);
		//DrawText("EASY", easyRec.x + 15, easyRec.y + 5, 20, DARKBROWN);
		//DrawRectangleRec(hardRec, YELLOW);
		//DrawText("HARD", hardRec.x + 15, hardRec.y + 5, 20, DARKBROWN);
	}
	else {
		game->render();
	}
}
