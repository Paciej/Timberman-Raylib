#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

bool Game::isHit(const std::string& side) {
	int whichBranch = 1;
	if (side == "Right") {
		whichBranch = 2;
	}
	return whichBranch == tree.tree[tree.tree.size() - 1].branch;
}

void Game::reset() {
	gameState = GameState::playing;
	tree.drawNewTree();
	player.moveLeft();
	player.setPlayerToWait();
	isPlayerDead = false;
	deathTimer = 0.0f;
	timer.resetTimer();
	isStarted = false;
	score = 0;
}

void Game::update() {

	if (gameState == GameState::playing) {
		HideCursor();
		if (timer.currentTime <= 0) {
			gameState = GameState::gameOver;
		}

		if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && !isPlayerDead) {
			isStarted = true;
			AudioManager::playSoundEffect(hitSound);
			player.moveLeft();

			tree.treeHit("Left");

			if (isHit("Left")) {
				player.setPlayerToRip();
				isStarted = false;
				AudioManager::playSoundEffect(deathSound);
			}
			else {
				timer.incrementTime();
				score += scoreMultip;
				std::cout << "Score: " << score << std::endl;
			}
		}
		else if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && !isPlayerDead) {
			isStarted = true;
			AudioManager::playSoundEffect(hitSound);
			player.moveRight();

			tree.treeHit("Right");

			if (isHit("Right")) {
				player.setPlayerToRip();
				isStarted = false;
				AudioManager::playSoundEffect(deathSound);
			}
			else {
				timer.incrementTime();
				score += scoreMultip;
				std::cout << "Score: " << score << std::endl;
			}
		}

		isPlayerDead = player.isPlayerDead();

		if (isPlayerDead) {
			deathTimer+= GetFrameTime();

			if (deathTimer >= deathDelay) {
				// Przejœcie do okna Game Over
				gameState = GameState::gameOver;
			}
		}

		if (gameState == GameState::gameOver) {
			ShowCursor();
			sceneGameOver = new SceneOver(score);
		}

		if (isStarted) {
			timer.update();
			player.Update();
		}
	} 
	else if (gameState == GameState::gameOver) {
		if (!sceneGameOver->playAgain) {
			sceneGameOver->Update();
			if (sceneGameOver->ShouldTransition()) {
				ShowCursor();
				backToMenu = true;
			}
		} else {
			sceneGameOver->playAgain = false;
			delete sceneGameOver;
			reset();
		}
	}

	tree.Update();
	clouds.Update();
	birds.Update();
}

void Game::render() {
	clouds.Render();
	birds.Render();
	tree.Render();
	player.Render();

	if (gameState == GameState::playing) {
		timer.render();
		DrawText(TextFormat("%i", score), 20, 20, 50, BLACK);
	}

	if (gameState == GameState::gameOver) {
		sceneGameOver->Render();
	}
}
