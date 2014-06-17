// SpriteManager.h

#pragma once

class SpriteManager {
public:
	static void Init(std::string _path);

	static sf::Sprite* GetSprite(const std::string& _fileName, int _locX = 0, int _locY = 0, int _sizeX = 0, int _sizeY = 0);

	static void CleanUp();

private:
	static void LoadImage(const std::string& _fileName);

private:
	static std::string m_directory;
	static std::map<std::string, sf::Texture*> m_sprites;
};
