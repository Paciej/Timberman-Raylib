#include "raylib.h"
#include <thread>
#include <chrono>
import RayFunctions;
export module Player;

#pragma once
export class Player {
private:
	float playerWidth = 155;
	float playerHeight = 190;
	float ripWidth = 100;
	float ripHeight = 75;
	float offset = 100;

	Vector2 positionLeft = { 1280.f / 2 - offset - playerWidth - 20.f, 640.f - playerHeight };
	Vector2 positionRight = { 1280.f / 2 + offset + 20.f, 640.f - playerHeight };
	Vector2 currentPosition = positionLeft;
	Rectangle posLeftRec = { positionLeft.x, positionRight.y, playerWidth, playerHeight };
	Rectangle posRightRec = { positionRight.x, positionRight.y, playerWidth, playerHeight };

	Texture2D playerWait;
	Texture2D playerHit;
	Texture2D playerRip;
	Texture2D currentPlayer;

	int frameCounter = 0;
	int backToWaitSpeed = 10;
	bool isMoved = false;
	bool died = false;

public:
	Player() {
		playerWait = getTextureFromAssetName("timbermanWait.png");
		playerHit = getTextureFromAssetName("timbermanHit.png");
		playerRip = getTextureFromAssetName("rip.png");
		currentPlayer = playerWait;
	}


	void moveLeft() {
		currentPosition = positionLeft;
		isMoved = true;
	}

	void moveRight() {
		currentPosition = positionRight;
		isMoved = true;
	}
	
	void setPlayerToRip() {
		currentPlayer = playerRip;
		died = true;
	}

	void setPlayerToWait() {
		died = false;
		currentPlayer = playerWait;
	}

	bool isPlayerDead() {
		return died;
	}

	void Update() {

		frameCounter++;
		if (isMoved) {
			frameCounter = 0;
			currentPlayer = playerHit;
			isMoved = false;
		}

		if ((frameCounter >= (60 / backToWaitSpeed) && currentPlayer.width != playerRip.width)) {
			frameCounter = 0;
			currentPlayer = playerWait;
		}
	}

	void Render() {
		//DrawRectangle((int)currentPosition.x, (int)currentPosition.y, playerWidth, playerHeight, RED);

		if (currentPosition.x == positionLeft.x) {
			DrawTexturePro(currentPlayer, { 0, 0, (float)currentPlayer.width, (float)currentPlayer.height }, posLeftRec, { 0, 0 }, 0.0f, WHITE);
		}
		else {

			if (currentPlayer.width == playerRip.width) {
				DrawTexturePro(currentPlayer, { 0, 0, (float)currentPlayer.width, (float)currentPlayer.height }, posRightRec, { 0, 0 }, 0.0f, WHITE);

			}
			else {
				DrawTexturePro(currentPlayer, { 0, 0, -(float)currentPlayer.width, (float)currentPlayer.height }, posRightRec, { 0, 0 }, 0.0f, WHITE);
			}
		}
	}
};