#ifndef GAME_H_
#define GAME_H_

#include "Tree.h"
#include "SceneOver.h"
import Birds;
import Clouds;
import Player;
import Timer;

class Game {
private:
	enum class GameState {
		playing,
		gameOver
	};
	GameState gameState = GameState::playing;
	bool isStarted = false;

	int score = 0;
	int scoreMultip;

	bool isPlayerDead = false;
	float deathTimer = 0.0f;
	float deathDelay = 1.85f;

	Player player;
	Birds birds;
	Tree tree;
	Clouds clouds;
	Timer timer;
	SceneOver* sceneGameOver = nullptr;
	Sound hitSound = getSoundFromName("punch.wav");
	Sound deathSound = getSoundFromName("dead.wav");

	bool isHit(const std::string& side);
	void reset();
public:
	bool backToMenu = false;
	Game(int scoreMultip, float time, float increment) : timer(time, increment), scoreMultip(scoreMultip) {
		//AudioManager::changeMainTheme(AudioManager::background);
	}

	void update();
	void render();
};
#endif // !GAME_H_