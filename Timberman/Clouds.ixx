#include "raylib.h"
#include <deque>
import RayFunctions;

export module Clouds;

#pragma once
export class Clouds {
private:
	Texture2D cloudTex;
	Vector2 position = { 1280, 150 };
	Vector2 origin = { (float)cloudTex.width / 8, (float)cloudTex.height };

	struct Cloud {
		Vector2 position;
		float speed;
		int currentFrame = 0;
		Rectangle frameRec;
	};

	int framesCounter = 0;
	int framesSpeed = 10;

	std::deque<Cloud> clouds;

	void createCloud(Cloud& newCloud);
	void resetCloud(Cloud& cloud);
	void moveCloud();

public:
	Clouds() {
		cloudTex = getTextureFromAssetName("cloud.png");

		for (int i = 0; i <= 3; i++) {
			Cloud newCloud;
			createCloud(newCloud);
		}

		for (auto& f : clouds)
			f.frameRec = { 0.0f, 0.0f, -(float)cloudTex.width / 8, (float)cloudTex.height };
	}


	void Update();
	void Render();
};