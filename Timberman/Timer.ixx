#include "raylib.h"
import RayFunctions;
export module Timer;

export class Timer {
private:
	Texture2D timeTexture;
	Texture2D frameTexture;
	Texture2D emptyTexture;

	Rectangle timeDestRec;
	Rectangle timeEmptyDestRec;
	Rectangle frameDestRec;

	unsigned int maxTime = 400;
	float frameWidth = 420;
	float frameHeight = 70;
	float timeWidth = maxTime;
	float timeHeight = frameHeight - 20;

	float timerSpeed;
	float increment;

	void decrementTime() {currentTime -= timerSpeed;}
public:
	float currentTime = maxTime;

	Timer(float& timerSpeed, float increment) : timerSpeed(timerSpeed), increment(increment) {
		timeTexture = getTextureFromAssetName("timebar.png");
		frameTexture = getTextureFromAssetName("timeframe.png");
		emptyTexture = getTextureFromAssetName("emptyBar.png");

		timeDestRec = { 0.5f * (1280 - timeWidth), 40, timeWidth, timeHeight };
		timeEmptyDestRec = timeDestRec;
		frameDestRec = { 0.5f * (1280 - frameWidth), 30, frameWidth, frameHeight };
	}

	void resetTimer() {
		currentTime = maxTime;
		timeDestRec.width = currentTime;
	}

	void incrementTime() {
		currentTime += increment;
		if (currentTime > maxTime) {
			currentTime = maxTime;
		}
	}

	void update() {
		decrementTime();
		timeDestRec.width = currentTime;
	}

	void render() {
		//DrawRectangle(427, 30, currentTime, frameHeight, RED);
		DrawTexturePro(emptyTexture,
			{ 0, 0, (float)emptyTexture.width, (float)emptyTexture.height },
			timeEmptyDestRec,
			{ 0,0 }, 0.0f, WHITE
		);

		DrawTexturePro(timeTexture,
			{ 0, 0, (float)emptyTexture.width, (float)emptyTexture.height },
			timeDestRec,
			{ 0,0 }, 0.0f, WHITE
		);

		DrawTexturePro(frameTexture,
			{ 0, 0, (float)frameTexture.width, (float)frameTexture.height },
			{ frameDestRec },
			{ 0,0 }, 0.0f, WHITE
		);
	}
};