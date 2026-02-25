#include "SceneMenu.h"

//private
void SceneMenu::createTiles() {
	for (int i = 0; i < tileRectangles.size()*0.5; i++) {
		Tile newTile;
		newTile.tilePos.x = 1280 * 0.5 - tileOffset;
		newTile.tilePos.y = 210 + 70 * i;
		newTile.destRec = {newTile.tilePos.x, newTile.tilePos.y, tileWidth, tileHeight};
		newTile.sourceRec = tileRectangles[i * 2];
		tilesVec.push_back(newTile);
	}
	tilesVec[0].tileScene = Scenes::gameScene;
	tilesVec[1].tileScene = Scenes::leaderboardScene;
	tilesVec[2].tileScene = Scenes::optionScene;
	tilesVec[3].tileScene = Scenes::Exit;
}

//public
bool SceneMenu::ShouldTransition() const {
	return changeScene;
}

Scene* SceneMenu::NextScene() const {
	switch (selectedScene) {
	case Scenes::gameScene:
		return new SceneGame();

	case Scenes::leaderboardScene:
		return new SceneLeaderboard();

	case Scenes::optionScene:
		return new SceneOptions();

	case Scenes::Exit:
		return nullptr;

	default:
		return nullptr;
	}
}

void SceneMenu::Update() {
	Vector2 mouseVirtual = getMouseVirtualPosition();

	for (size_t i = 0; i < tilesVec.size(); i++) {
		if (CheckCollisionPointRec(mouseVirtual, tilesVec[i].destRec)) {
			if (i == 1) {
				currentScore = scorePressed;
			}
			else {
				tilesVec[i].sourceRec = tileRectangles[i * 2 + 1];
			}
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				selectedScene = tilesVec[i].tileScene;
				changeScene = true;
			}
		}
		else {
			if (i == 1) {
				currentScore = score;
			} else {
				tilesVec[i].sourceRec = tileRectangles[i * 2];
			}
		}
	}
}

void SceneMenu::Render() {
	//main title
	//DrawRectangle(1280 / 2 - gameTitleOffset, 60, gameTitleWidth, gameTitleHeight, DARKGREEN);
	DrawTexturePro(titleTexture,
		{ 0, 0, (float)titleTexture.width, (float)titleTexture.height, },
		{ 1280 / 2 - gameTitleOffset, 60, gameTitleWidth, gameTitleHeight },
		{ 0,0 }, 0.0f, WHITE
	);
	//DrawText("TIMBERMAN", 1280 / 2 - 200, 70, 60, ORANGE);

	//wood background
	DrawTexturePro(gui, woodRec, { 1280 / 2 - woodOffset, 720 / 5, woodWidth, woodHeight }, { 0, 0 }, 0.0f, WHITE);
	
	//Tiles
	for (auto& tile : tilesVec) {
		if (tile.tileScene != Scenes::leaderboardScene) {
			DrawTexturePro(gui, tile.sourceRec, tile.destRec, { 0, 0 }, 0.0f, WHITE);
		}
		else {
			DrawTexturePro(currentScore, { 0, 0, (float)score.width, (float)score.height }, tile.destRec, { 0, 0 }, 0.0f, WHITE);
		}
	}
}