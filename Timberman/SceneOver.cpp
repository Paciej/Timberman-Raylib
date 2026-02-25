#include "SceneOver.h"
#include <regex>

void SceneOver::insertText(Vector2& mousePos) {

	int key = GetCharPressed();

	while (key > 0) {

		if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
			nickname[letterCount] = (char)key;
			nickname[letterCount + 1] = '\0';
			letterCount++;
		}
		key = GetCharPressed();
	}
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		letterCount--;
		if (letterCount < 0) letterCount = 0;
		nickname[letterCount] = '\0';
	}
}

std::string SceneOver::nicknameAccuracyText(char newNickname[MAX_INPUT_CHARS + 1])
{
	std::regex nickRegex("^[A-Za-z][A-Za-z0-9]{2,}$");

	if (scoreIsSaved) {
		return "Score is already saved";
	}

	for (size_t i = 0; i < MAX_INPUT_CHARS; i++) {
		char currentChar = newNickname[i];
		if (currentChar == ' ') {
			return "Nickname cannot contain space";
			
		}
		if (currentChar == '\0' && i < 3) {
			return "Nickname must contain at least 3 characters";
		}
	}

	if (std::regex_match(nickname, nickRegex)) {
		if (scoreFile.good()) {
			scoreFile << gameScore << "\t" << nickname << std::endl;
			scoreIsSaved = true;
		}
		else {
			std::cerr << "\nERROR: BLAD Z PLIKIEM PODCZAS WPISYWANIA\n";
		}
	}
	else {
		if (std::isdigit(nickname[0])) {
			return "Nickname cannot start with a digit";
		}
		return "Nickname cannot contain special characters";
	}

	return "Score has been saved successfully";
}

Scene* SceneOver::NextScene() const {
    return nullptr;
}

bool SceneOver::ShouldTransition() const {

    return backToMenu;
}

void SceneOver::Update() {
	Vector2 mouseVirtual = getMouseVirtualPosition();

	if (CheckCollisionPointRec(mouseVirtual, textBox)) {
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		insertText(mouseVirtual);
	}
	else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}

	if (CheckCollisionPointRec(mouseVirtual, replayRec)) {
		replayCol = GRAY;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			playAgain = true;
		}
	}
	else if (CheckCollisionPointRec(mouseVirtual, menuRec)) {
		menuCol = GRAY;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			backToMenu = true;
		}

	}
	else {
		replayCol = WHITE;
		menuCol = WHITE;
	} 
	if (IsKeyPressed(KEY_ENTER)) {
		answer = nicknameAccuracyText(nickname);
		for (size_t i = 0; i < letterCount; i++) {
			nickname[i] = '\0';
		}
		letterCount = 0;
		insertNickname = true;
		frameCounter = 0;
	}
	frameCounter++;
}

void SceneOver::Render() {
    //background
    //DrawRectangle(backPosX, 720 * 0.3, backWidth, backHeight, BROWN);
	DrawTexturePro(gui, backSrcRec, backDestRec, { 0,0 }, 0.0f, WHITE);

	DrawText(TextFormat("Score: %i", gameScore), backPosX + 140, lowBackPosY - 300, 50, WHITE);

	//text window
	DrawRectangleRec(textBox, WHITE);
	DrawText(nickname, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

	//answer
	if (insertNickname) {
		DrawText(answer.c_str(), backPosX + 160 - (2 * answer.size()), textBox.y + textBoxHeight + 10, 15, WHITE);
		if (frameCounter > 180) {
			insertNickname = false;
		}
	}

    //tiles (zagraj ponownie) (Menu glowne) - zastapie przyciski obrazkami domku oraz strzalki z powtorka
	DrawTexturePro(replayTexture, {0.0f, 0.0f, 40, 30}, replayRec, {0, 0}, 0.0f, replayCol);
	//DrawRectangleRec(replayRec, replayCol);
	DrawTexturePro(menuTexture, { 0.0f, 0.0f, 40, 30 }, menuRec, { 0, 0 }, 0.0f, menuCol);
	//DrawRectangleRec(menuRec, menuCol);
}
