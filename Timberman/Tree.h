#pragma once
#include "raylib.h"
#include <deque>
#include <string>
import RayFunctions;

class Tree {
private:
	enum branchSide {
		none,
		left,
		right
	};

	struct Log {
		Vector2 position;
		branchSide branch;
	};

	struct ChopDownLog {
		Log log;
		Vector2 velocity;
		float gravity = 1;
		float deltaTime = 0;
	};

	Texture2D logTexture;
	Texture2D branchTexture;
	Texture2D treeRootTexture;

	float treeWidth = 200;
	float treeHeight = 150;
	float offset = treeWidth * 0.5;
	float treeCenter = 1280 * 0.5 - offset;
	const int logCount = 6;

	std::deque<ChopDownLog> cutLogs;

	branchSide getRandBranchSize() { return static_cast<branchSide>(GetRandomValue(0, 2)); }
	void addNewLog();

public:
	std::deque<Log> tree;

	Tree(){
		logTexture = getTextureFromAssetName("log.png");
		branchTexture = getTextureFromAssetName("branch.png");
		treeRootTexture = getTextureFromAssetName("treeRoot.png");
		drawNewTree();
	}

	void drawNewTree();
	void treeHit(const std::string& side);
	void Update();
	void Render();
};

