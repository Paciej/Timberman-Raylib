#include "raylib.h"
import Clouds;

void Clouds::createCloud(Cloud& newCloud) {

	newCloud.speed = GetRandomValue(1, 100) * 0.01;
	newCloud.position.x = GetRandomValue(1000, 1800);
	newCloud.position.y = GetRandomValue(50, 250);
	clouds.push_back(newCloud);
}

void Clouds::resetCloud(Cloud& cloud) {

	cloud.speed = GetRandomValue(1, 100) * 0.01;
	cloud.position.x = GetRandomValue(1280, 1700);
	cloud.position.y = GetRandomValue(70, 270);
}

void Clouds::moveCloud() {
	for (auto& cloud : clouds) {
		cloud.position.x -= cloud.speed;
		if (cloud.position.x < -125) {
			resetCloud(cloud);
		}
	}
}

void Clouds::Update() {
	//moveCloud();
	//framesCounter++;
	//if (framesCounter >= (60 / framesSpeed)) {
	//	framesCounter = 0;
	//	for (auto& f : clouds) {
	//		f.currentFrame++;
	//		if (f.currentFrame > 7) {
	//			f.currentFrame = 0;
	//		}
	//		f.frameRec.x = (float)f.currentFrame * (float)cloudTex.width / 8;
	//	}
	//}
}

void Clouds::Render() {
	//for (auto& cloud : clouds) {
	//	DrawTexturePro(cloudTex, cloud.frameRec, { cloud.position.x, cloud.position.y, 120, 80 }, origin, 0.0f, WHITE);
	//}
}
