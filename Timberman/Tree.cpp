#include "Tree.h"

// Private functions
void Tree::addNewLog() {
	float topY = tree.front().position.y - treeHeight;
	
	Log log{ 
		Vector2{ treeCenter, topY }, 
		getRandBranchSize() 
	};

	tree.insert(tree.begin(), log);
}


// Public Functions
void Tree::drawNewTree() {

	cutLogs.clear();
	tree.clear();
	Log log{
		Vector2{ treeCenter, 450 },
		none
	};
	tree.push_front(log);


	for (int i = 1; i <= logCount; i++) {
		float topY = tree.front().position.y - treeHeight;
		Log log{
			Vector2{ treeCenter, topY },
			getRandBranchSize()
		};
		tree.push_front(log);
	}
}

void Tree::treeHit(const std::string& side) {

	ChopDownLog newCut;
	newCut.log = tree[tree.size() - 1];
	newCut.velocity.y = -10;
	addNewLog();

	for (auto& log : tree) {
		log.position.y += treeHeight;
	}
	if (side == "Left") {
		newCut.velocity.x = -25;
	}
	else {
		newCut.velocity.x = 25;
	}
	cutLogs.push_back(newCut);
	tree.pop_back();
}

void Tree::Update() {
	for (auto& cutLog : cutLogs) {
		cutLog.log.position.x += cutLog.velocity.x;
		cutLog.log.position.y += cutLog.velocity.y + cutLog.gravity * cutLog.deltaTime;

		if (cutLog.log.position.x > 1320 || cutLog.log.position.y > 760) {
			cutLogs.pop_front();
		}

		cutLog.deltaTime += 1;
	}
}

void Tree::Render() {
	for (size_t i = 0; i < tree.size(); i++) {

		//draw tree root
		DrawTexturePro(
			treeRootTexture,
			{ 0, 0, (float)treeRootTexture.width, (float)treeRootTexture.height },
			{ treeCenter - 20, tree[tree.size() - 1].position.y + treeHeight, treeWidth + 40, 48},
			{ 0,0 }, 0.0f, WHITE
		);

		//draw log
		//DrawRectangle(tree[i].position.x, tree[i].position.y, treeWidth, treeHeight, DARKBROWN);
		DrawTexturePro(logTexture, 
			{ 0, 0, (float)logTexture.width, (float)logTexture.height }, 
			{ tree[i].position.x, tree[i].position.y, treeWidth, treeHeight }, 
			{ 0,0 }, 0.0f, WHITE);

		//draw brunches
		if (tree[i].branch == left) {
			//DrawRectangle(tree[i].position.x - treeWidth, tree[i].position.y + treeHeight * 0.5, treeWidth, 40, DARKBROWN);
			DrawTexturePro(branchTexture,
				{ 0, 0, -(float)branchTexture.width, (float)branchTexture.height },
				{ tree[i].position.x - treeWidth - 30, tree[i].position.y + (float)(treeHeight * 0.5), treeWidth + 30, 40},
				{ 0,0 }, 0.0f, WHITE
			);
		}
		else if (tree[i].branch == right) {
			//DrawRectangle(tree[i].position.x + treeWidth, tree[i].position.y + treeHeight * 0.5, treeWidth, 40, DARKBROWN);
			DrawTexturePro(branchTexture,
				{ 0, 0, (float)branchTexture.width, (float)branchTexture.height },
				{ tree[i].position.x + treeWidth, tree[i].position.y + (float)(treeHeight * 0.5), treeWidth + 30, 40 },
				{ 0,0 }, 0.0f, WHITE
			);
		}
	}

	for (size_t i = 0; i < cutLogs.size(); i++) {
				DrawTexturePro(logTexture, 
			{ 0, 0, (float)logTexture.width, (float)logTexture.height }, 
			{ cutLogs[i].log.position.x, cutLogs[i].log.position.y, treeWidth, treeHeight }, 
			{ 0,0 }, 0.0f, WHITE);
	}
}
