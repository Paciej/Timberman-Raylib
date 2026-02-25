#include "raylib.h"
import Birds;

void Birds::moveBird(Bird& bird) {
	bird.position.x += bird.speed;
	if (bird.position.x >= 1280 + birdWidth) {
		resetBird(bird);
	}
}

void Birds::resetBird(Bird& bird) {
	bird.position.x = GetRandomValue(-100, 0);
	bird.position.y = GetRandomValue(50, 250);
	bird.speed = GetRandomValue (3, 8) * 0.1;
}

Birds::Bird Birds::createBird() {
	Bird newBird;
	newBird.position.x = GetRandomValue(-300, 1280);
	newBird.position.y = GetRandomValue(50, 250);
	newBird.currentFrame = GetRandomValue(0, 8);
	newBird.speed = GetRandomValue (3, 8) * 0.1;
	newBird.frameRec = { 0.0f, 0.0f, (float)texture.width / 8, (float)texture.height };
	return newBird;
}

void Birds::Update() {
	frameCounter++;

	for (auto& bird : birds) {
		moveBird(bird);
	}
	if (frameCounter >= 60 / frameSpeed) {
		frameCounter = 0;
		for (auto& bird : birds) {
			bird.currentFrame++;
			if (bird.currentFrame > 7) {
				bird.currentFrame = 0;
			}
			bird.frameRec.x = (float)bird.currentFrame * (float)texture.width / 8;

		}
	}
}

void Birds::Render() {
	for (auto& bird : birds) {
		DrawTexturePro(texture, bird.frameRec, { bird.position.x, bird.position.y, 50, 40 }, {0, 0}, 0.0f, WHITE);
	}
}
