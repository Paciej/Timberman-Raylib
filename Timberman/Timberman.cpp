#include "SceneMenu.h"
#include <filesystem>
import ResManager;  
import AudioManager;
import RayFunctions;

const int VIRTUAL_WIDTH = 1280;
const int VIRTUAL_HEIGHT = 720;

int main() {
    
    bool shouldRestart = false;
    
    do {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(ResManager::GetWidth(), ResManager::GetHeight(), "Timberman");

        Texture2D floorTexture = getTextureFromAssetName("floor2.png");
        Texture2D bgTexture = getTextureFromAssetName("background.png");

        AudioManager::initAudio();
        Music mainTheme = getMusicFromName("main_theme.mp3");
        AudioManager::currentTheme = mainTheme;
        AudioManager::playMainTheme(AudioManager::currentTheme);

        Scene* currentScene = new SceneMenu();

        RenderTexture2D target = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
        SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

        bool gameRunning = true;
        SetTargetFPS(60);
        while (gameRunning && !WindowShouldClose()) {
            if (!AudioManager::musicIsMuted()) {
                UpdateMusicStream(AudioManager::currentTheme);
            }
            currentScene->Update();

            BeginTextureMode(target);
            DrawTexturePro(bgTexture,
                { 0, 0, (float)bgTexture.width, (float)bgTexture.height },
                { 0, 0, 1280.f, 720.f },
                { 0,0 }, 0.0f, WHITE
            );
            DrawTexturePro(floorTexture,
                { 0, 0, (float)floorTexture.width, (float)floorTexture.height },
                { 0, 560, 1280.f, 160.f},
                { 0,0 }, 0.0f, WHITE
            );
            currentScene->Render();
            EndTextureMode();

            BeginDrawing();
            ClearBackground(BLACK);

            float scaleX = (float)GetScreenWidth() / VIRTUAL_WIDTH;
            float scaleY = (float)GetScreenHeight() / VIRTUAL_HEIGHT;
            float scale = (float)fmin(scaleX, scaleY);
            int offsetX = (GetScreenWidth() - VIRTUAL_WIDTH * scale) / 2;
            int offsetY = (GetScreenHeight() - VIRTUAL_HEIGHT * scale) / 2;

            DrawTexturePro(
                target.texture,
                Rectangle{ 0, 0, (float)VIRTUAL_WIDTH, -(float)VIRTUAL_HEIGHT },
                Rectangle{ (float)offsetX, (float)offsetY, VIRTUAL_WIDTH * scale, VIRTUAL_HEIGHT * scale },
                Vector2{ 0, 0 },
                0.0f,
                WHITE
            );

            EndDrawing();

            if (ResManager::NeedsRestart()) {
                shouldRestart = true;
                gameRunning = false;
            }

            if (currentScene->ShouldTransition()) {
                Scene* next = currentScene->NextScene();
                if (next == nullptr) {
                    gameRunning = false;
                    shouldRestart = false;
                }
                else {
                    delete currentScene;
                    currentScene = next;
                }
            }
        }

        UnloadRenderTexture(target);
        delete currentScene;
        AudioManager::closeMusic();
        CloseWindow();

    } while (shouldRestart);
    return 0;
}

/*
* ========================================
*           RZECZY DO ZROBIENIA
* ========================================
*
* - Poziomy trudnosci: szybsze zuzycie paska czasu w celu zdobywania wiekszej ilosci punktow *DONE*
* - UI: Punktacja, obramowanie dla paska czasu *DONE*
* - Menu po przegranej z uzyskanymi punktami, mozliwoscia zagrania znowu oraz powrotu do menu glownego *DONE*
* - Ustawienia: Wyciszenie gry, zmiana rozdzielczosci *DONE*
* - Tabela wynikow: top 10 wynikow *DONE*
* - Menu glowne: Opcje: zagraj, tabela wynikow, ustawienia, wyjscie *DONE*
* - Assety: Gracz, galaz, tlo, trawa, menu *DONE*
* - Dzwieki: uderzanie toporem w drzewo, dzwiek przegranej, muzyka w tle *DONE*
* 
* ========================================
*              BIBLIOTEKI
* ========================================
*
* - filesystem: sprawdzanie istnienie plikÛw, obs≥uga pliku do tabeli wynikÛw *DONE*
* - modules: zamiana plikÛw naglowkowych na modu≥y *DONE*
* - regex: ograniczenie wprowadzenia nicku uzytkownika do pewnych znakow *DONE*
* - concepts
*
* ========================================
*          NA P”èNIEJSZY ROZW”J
* ========================================
* - Skiny za zdobywanie punktow 
* - Cykl dnia i nocy 
* - Dzwieki otoczenia: ptaki, wiatr 
* - animacje podczas zmian sceny
*/