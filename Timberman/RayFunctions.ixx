#include "raylib.h"
#include <filesystem>
#include <iostream>
#include <concepts>
export module RayFunctions;

export template<typename T>
concept PathCompatible = requires(T t) {
	{ std::filesystem::path(t) };
};

export Vector2 getMouseVirtualPosition() {
	Vector2 mouse = GetMousePosition();
	Vector2 screenSize = { GetScreenWidth(), GetScreenHeight() };

	float scaleX = 0;
	float scaleY = 0;

	scaleX = 1280.0f / screenSize.x;
	scaleY = 720.0f / screenSize.y;

	return {
		(float)mouse.x * scaleX,
		(float)mouse.y * scaleY
	};
}

export Rectangle getSpriteRec(int col, int row, int width = 1, int height = 1, int tileSize = 32){
	//Rodzaj assetow (0, 8, 16)
	int assetType = 8;
	return Rectangle{ (float)(col + assetType) * tileSize, (float)row * tileSize, (float)tileSize * width, (float)tileSize * height};
}

template <PathCompatible T>
std::string resolveTexturePath(const T& assetName) {
	std::filesystem::path assetPath = std::filesystem::current_path() / "Resources" / "Assets" / assetName;
	if (!std::filesystem::exists(assetPath)) {
		TraceLog(LOG_ERROR, TextFormat("Texture file not found: %s", assetPath.string().c_str()));
		return ""; // Zwraca pust¹ œcie¿kê
	}
	return assetPath.string();
}

export Texture2D getTextureFromAssetName(const std::string& assetName) {
	std::string pathStr = resolveTexturePath(assetName);
	if (pathStr.empty()) return Texture2D{};
	return LoadTexture(pathStr.c_str());
}

export template <PathCompatible T>
Sound getSoundFromSoundName(const T& soundName){
	std::filesystem::path soundPath = std::filesystem::current_path() / "Resources" / "Sounds" / soundName;
	if (!std::filesystem::exists(soundPath)) {
		TraceLog(LOG_ERROR, TextFormat("Sound file not found: %s", soundPath.string().c_str()));
		return Sound{};
	}

	return LoadSound(soundPath.string().c_str());
}
