#include "SceneLeaderboard.h"
#include "SceneMenu.h"

std::vector<SceneLeaderboard::ScoreEntry> SceneLeaderboard::loadScoresFromFile(const std::string& filename) {
    std::vector<ScoreEntry> scores;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Nie uda³o siê otworzyæ pliku: " << filename << std::endl;
        return scores;
    }

    int score;
    std::string nickname;
    while (file >> score >> nickname) {
        scores.push_back({ score, nickname });
    }

    file.close();
    return scores;
}

std::vector<SceneLeaderboard::ScoreEntry> SceneLeaderboard::getTop10Scores()
{
    std::vector<ScoreEntry> topScores = loadScoresFromFile("Scoreboard.txt");

    std::sort(topScores.begin(), topScores.end()); // u¿ywa operator< z struct ScoreEntry

    if (topScores.size() > 10)
        topScores.resize(10); // przycinamy do top 10

    return topScores;
}

Scene* SceneLeaderboard::NextScene() const
{
    return new SceneMenu();
}

bool SceneLeaderboard::ShouldTransition() const
{
    return backToMenu;
}

void SceneLeaderboard::Update() {
    Vector2 virtualMouse = getMouseVirtualPosition();
    if (CheckCollisionPointRec(virtualMouse, buttonDestRec)) {
        currentButton = buttonPressedSrcRec;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            backToMenu = true;
        }
    }
    else {
        currentButton = buttonSrcRec;
    }

    if (IsKeyPressed(KEY_B)) {
        backToMenu = true;
    }
}

void SceneLeaderboard::Render() {
    
    //DrawRectangleRec(bgRec, BROWN);
    DrawTexturePro(bgTexture, bgSourceRec, bgDestRec, { 0, 0 }, 0.0f, WHITE);
    for (size_t i = 0; i < topTenScores.size(); i++) {
        DrawText(TextFormat("%2zu. %s - %d", i + 1, topTenScores[i].nickname.c_str(), topTenScores[i].score), 
            textPosX, textPosY + (39 * i), 20, WHITE);
    }

    DrawTexturePro(bgTexture, currentButton, buttonDestRec, { 0, 0 }, 0.0f, WHITE);
}
