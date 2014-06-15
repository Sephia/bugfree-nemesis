// SpriteManager.h

#pragma once

class SpriteManager {
public:
	static void Init(std::string path);

	static sf::Sprite* GetSprite(const std::string fileName);

	static void CleanUp();

private:
	static sf::Sprite* LoadImage();

private:
	static std::string m_directory;
	static std::map<std::string, sf::Texture*> m_sprites;
};
