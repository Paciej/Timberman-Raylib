#include "raylib.h"
#include <deque>
import RayFunctions;

export module Birds;

export class Birds {
private:
	struct Bird {
		Vector2 position;
		float speed;
		int currentFrame;
		Rectangle frameRec;
	};

	int frameCounter = 0;
	int frameSpeed = 5;

	float birdWidth = 50;
	float birdHeight = 30;
	int birdCount = 3;

	Texture2D texture;	

	std::deque<Bird> birds;

	void moveBird(Bird& bird);
	void resetBird(Bird& bird);
	Bird createBird();
public:
	Birds() {
		texture = getTextureFromAssetName("bird.png");

		for (int i = 0; i < birdCount; i++) {
			birds.push_back(createBird());
		}
	}

	void Update();
	void Render();
};